#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT64 ;
typedef  size_t UINT ;
typedef  void* UCHAR ;
struct TYPE_4__ {size_t NumAck; size_t* AckPacketId; size_t PacketId; size_t DataSize; int /*<<< orphan*/  Data; void* YourSessionId; void* MySessionId; void* KeyId; void* OpCode; } ;
typedef  TYPE_1__ OPENVPN_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (void**,size_t) ; 
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENVPN_MAX_NUMACK ; 
 TYPE_1__* ZeroMalloc (int) ; 

OPENVPN_PACKET *OvsNewControlPacket(UCHAR opcode, UCHAR key_id, UINT64 my_channel_id, UINT num_ack,
									UINT *ack_packet_ids, UINT64 your_channel_id, UINT packet_id,
									UINT data_size, UCHAR *data)
{
	OPENVPN_PACKET *p = ZeroMalloc(sizeof(OPENVPN_PACKET));
	UINT i;

	p->OpCode = opcode;
	p->KeyId = key_id;
	p->MySessionId = my_channel_id;
	p->NumAck = num_ack;

	for (i = 0;i < MIN(num_ack, OPENVPN_MAX_NUMACK);i++)
	{
		p->AckPacketId[i] = ack_packet_ids[i];
	}

	p->YourSessionId = your_channel_id;
	p->PacketId = packet_id;

	if (data_size != 0 && data != NULL)
	{
		p->Data = Clone(data, data_size);
		p->DataSize = data_size;
	}

	return p;
}