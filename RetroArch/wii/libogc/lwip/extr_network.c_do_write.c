#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  copy; int /*<<< orphan*/  dataptr; } ;
struct TYPE_10__ {TYPE_2__ w; } ;
struct apimsg_msg {TYPE_7__* conn; TYPE_3__ msg; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_8__ {TYPE_4__* tcp; } ;
struct TYPE_12__ {int type; int /*<<< orphan*/  mbox; int /*<<< orphan*/  (* callback ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ pcb; int /*<<< orphan*/  err; } ;
struct TYPE_11__ {int flags; int snd_queuelen; int /*<<< orphan*/  unacked; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_MSG_DEBUG ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTSENDMINUS ; 
#define  NETCONN_RAW 132 
#define  NETCONN_TCP 131 
#define  NETCONN_UDP 130 
#define  NETCONN_UDPLITE 129 
#define  NETCONN_UDPNOCHKSUM 128 
 int /*<<< orphan*/  TCP_SNDLOWAT ; 
 int TF_NODELAY ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_output (TYPE_4__*) ; 
 int /*<<< orphan*/  tcp_sndbuf (TYPE_4__*) ; 
 int /*<<< orphan*/  tcp_write (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_write(struct apimsg_msg *msg)
{
	err_t err;
	u32 dummy = 0;

	if(msg->conn->pcb.tcp) {
		switch(msg->conn->type) {
			case NETCONN_RAW:
			case NETCONN_UDPLITE:
			case NETCONN_UDPNOCHKSUM:
			case NETCONN_UDP:
				msg->conn->err = ERR_VAL;
				break;
			case NETCONN_TCP:
				err = tcp_write(msg->conn->pcb.tcp,msg->msg.w.dataptr,msg->msg.w.len,msg->msg.w.copy);
				if(err==ERR_OK && (!msg->conn->pcb.tcp->unacked || (msg->conn->pcb.tcp->flags&TF_NODELAY)
					|| msg->conn->pcb.tcp->snd_queuelen>1)) {
					LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: TCP write: tcp_output.\n"));
					tcp_output(msg->conn->pcb.tcp);
				}
				msg->conn->err = err;
				if(msg->conn->callback) {
					if(err==ERR_OK) {
						if(tcp_sndbuf(msg->conn->pcb.tcp)<=TCP_SNDLOWAT)
							(*msg->conn->callback)(msg->conn,NETCONN_EVTSENDMINUS,msg->msg.w.len);
					}
				}
				break;
			default:
				break;
		}
	}
	MQ_Send(msg->conn->mbox,&dummy,MQ_MSG_BLOCK);
}