#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {int tv_sec; } ;
struct TYPE_8__ {scalar_t__ direction; int status; scalar_t__ seq_n_0_cln; scalar_t__ ack_cln; scalar_t__ ack_srv; TYPE_1__ last_timestamp; TYPE_1__ timestamp_block; scalar_t__ seq_n_0_srv; TYPE_1__ syn_ack_timestamp; TYPE_1__ syn_timestamp; int /*<<< orphan*/  bytes_srv_to_cln; int /*<<< orphan*/  pkts_srv_to_cln; int /*<<< orphan*/  bytes_cln_to_srv; int /*<<< orphan*/  pkts_cln_to_srv; } ;
typedef  TYPE_2__ tcp_data ;
struct TYPE_10__ {int* buffer; } ;
struct TYPE_9__ {int key_len; } ;
typedef  TYPE_3__ TME_DATA ;
typedef  TYPE_4__ MEM_TYPE ;

/* Variables and functions */
 int ACK ; 
#define  CLOSED_FIN 136 
#define  CLOSED_RST 135 
#define  ERROR_TCP 134 
#define  ESTABLISHED 133 
 int FIN ; 
#define  FIN_CLN_RCV 132 
#define  FIN_SRV_RCV 131 
 scalar_t__ MAX_WINDOW ; 
 int RST ; 
 scalar_t__ SW_ULONG_AT (int*,int) ; 
 int SYN ; 
#define  SYN_ACK_RCV 130 
#define  SYN_RCV 129 
 scalar_t__ TME_SUCCESS ; 
 scalar_t__ ULONG_AT (int*,int) ; 
#define  UNKNOWN 128 

uint32 tcp_session(uint8 *block, uint32 pkt_size, TME_DATA *data, MEM_TYPE *mem_ex, uint8 *mem_data)

{

	uint32 next_status;  
	uint32 direction=ULONG_AT(mem_data,12);
	uint8 flags=mem_ex->buffer[25];
	tcp_data *session=(tcp_data*)(block+data->key_len*4);
	
	session->last_timestamp=session->timestamp_block;
	session->timestamp_block.tv_sec=0x7fffffff;
	
	if (direction==session->direction)
	{
		session->pkts_cln_to_srv++;
		session->bytes_cln_to_srv+=pkt_size;
	}
	else
	{
		session->pkts_srv_to_cln++;
		session->bytes_srv_to_cln+=pkt_size;
	}
	/* we use only thes four flags, we don't need PSH or URG */
	flags&=(ACK|FIN|SYN|RST);
	
	switch (session->status)
	{
	case ERROR_TCP:
		next_status=ERROR_TCP;
		break;
	
	case UNKNOWN:
		if (flags==SYN)
		{
			if (SW_ULONG_AT(mem_ex->buffer,20)!=0)
			{

				next_status=ERROR_TCP;
				break;
			}
			next_status=SYN_RCV;
			session->syn_timestamp=session->last_timestamp;

			session->direction=direction;
			session->seq_n_0_cln=SW_ULONG_AT(mem_ex->buffer,16);
		}
		else
			next_status=UNKNOWN;
		break;

	case SYN_RCV:
		if ((flags&RST)&&(direction!=session->direction))
		{
			next_status=CLOSED_RST;
			break;
		}
		if ((flags==SYN)&&(direction==session->direction))
		{	/* two syns... */
			next_status=SYN_RCV;
			session->seq_n_0_cln=SW_ULONG_AT(mem_ex->buffer,16);
			break;
		}
						
		if ((flags==(SYN|ACK))&&(direction!=session->direction))
		{		
			if (SW_ULONG_AT(mem_ex->buffer,20)!=session->seq_n_0_cln+1)
			{
				next_status=ERROR_TCP;
				break;
			}
			next_status=SYN_ACK_RCV;
			
			session->syn_ack_timestamp=session->last_timestamp;

			session->seq_n_0_srv=SW_ULONG_AT(mem_ex->buffer,16);
			session->ack_cln=session->seq_n_0_cln+1;
		}
		else
		{
			next_status=ERROR_TCP;
		}
		break;

	case SYN_ACK_RCV:
		if ((flags&ACK)&&(flags&RST)&&(direction==session->direction))
		{
			next_status=CLOSED_RST;
			session->ack_srv=SW_ULONG_AT(mem_ex->buffer,20);
			break;
		}
		
		if ((flags==ACK)&&(!(flags&(SYN|FIN|RST)))&&(direction==session->direction))
		{
			if (SW_ULONG_AT(mem_ex->buffer,20)!=session->seq_n_0_srv+1)
			{
				next_status=ERROR_TCP;
				break;
			}
			next_status=ESTABLISHED;
			session->ack_srv=session->seq_n_0_srv+1;
			break;
		}
		if ((flags&ACK)&&(flags&SYN)&&(direction!=session->direction))
		{
			next_status=SYN_ACK_RCV;
			break;
		}

		next_status=ERROR_TCP;
		break;
	
	case ESTABLISHED:
		if (flags&SYN)
		{
			if ((flags&ACK)&&
				(direction!=session->direction)&&
				((session->ack_cln-SW_ULONG_AT(mem_ex->buffer,20))<MAX_WINDOW)
				)
			{	/* SYN_ACK duplicato */
				next_status=ESTABLISHED;
				break;
			}
			
			if ((!(flags&ACK))&&
				(direction==session->direction)&&
				(SW_ULONG_AT(mem_ex->buffer,16)==session->seq_n_0_cln)&&
				(ULONG_AT(mem_ex->buffer,20)==0)
				)
			{	/* syn duplicato */
				next_status=ESTABLISHED;
				break;
			}
						
			next_status=ERROR_TCP;
			break;
		}
		if (flags&ACK)
			if (direction==session->direction)
			{
				uint32 new_ack=SW_ULONG_AT(mem_ex->buffer,20);
				if (new_ack-session->ack_srv<MAX_WINDOW)
					session->ack_srv=new_ack;
			}
			else
			{
				uint32 new_ack=SW_ULONG_AT(mem_ex->buffer,20);
				if (new_ack-session->ack_cln<MAX_WINDOW)
					session->ack_cln=new_ack;
			}
		if (flags&RST)
		{
			next_status=CLOSED_RST;
			break;
		}
		if (flags&FIN)
			if (direction==session->direction)
			{   /* an hack to make all things work */
				session->ack_cln=SW_ULONG_AT(mem_ex->buffer,16);
				next_status=FIN_CLN_RCV;
				break;
			}
			else
			{
				session->ack_srv=SW_ULONG_AT(mem_ex->buffer,16);
				next_status=FIN_SRV_RCV;
				break;
			}
		next_status=ESTABLISHED;
		break;
	
	case CLOSED_RST:
		next_status=CLOSED_RST;
		break;
	
	case FIN_SRV_RCV:	
		if (flags&SYN)
		{
			next_status=ERROR_TCP;
			break;
		}
			
		next_status=FIN_SRV_RCV;
		
		if (flags&ACK)
		{
			uint32 new_ack=SW_ULONG_AT(mem_ex->buffer,20);
			if (direction!=session->direction)
				if ((new_ack-session->ack_cln)<MAX_WINDOW)
					session->ack_cln=new_ack;
		}
		
		if (flags&RST)
			next_status=CLOSED_RST;
		else
			if ((flags&FIN)&&(direction==session->direction))
			{
				session->ack_cln=SW_ULONG_AT(mem_ex->buffer,16);
				next_status=CLOSED_FIN;
			}

		break;

	case FIN_CLN_RCV:
		if (flags&SYN)
		{
			next_status=ERROR_TCP;
			break;
		}
			
		next_status=FIN_CLN_RCV;
		
		if (flags&ACK)
		{
			uint32 new_ack=SW_ULONG_AT(mem_ex->buffer,20);
			if (direction==session->direction)
				if (new_ack-session->ack_srv<MAX_WINDOW)
					session->ack_srv=new_ack;
		}
		
		if (flags&RST)
			next_status=CLOSED_RST;
		else
			if ((flags&FIN)&&(direction!=session->direction))
			{
				session->ack_srv=SW_ULONG_AT(mem_ex->buffer,16);
				next_status=CLOSED_FIN;
			}

		break;

	case CLOSED_FIN:
			next_status=CLOSED_FIN;
		break;
	default:
		next_status=ERROR_TCP;

	}

	session->status=next_status;
	
	if ((next_status==CLOSED_FIN)||(next_status==UNKNOWN)||(next_status==CLOSED_RST)||(next_status==ERROR_TCP))
		session->timestamp_block=session->last_timestamp;
	
	return TME_SUCCESS;
}