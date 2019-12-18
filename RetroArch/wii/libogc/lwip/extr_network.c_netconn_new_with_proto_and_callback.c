#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct TYPE_7__ {TYPE_2__ bc; } ;
struct TYPE_8__ {struct netconn* conn; TYPE_3__ msg; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tcp; } ;
struct netconn {scalar_t__ err; int type; void (* callback ) (struct netconn*,int,u32) ;int /*<<< orphan*/  mbox; TYPE_4__ msg; scalar_t__ recvavail; scalar_t__ socket; int /*<<< orphan*/  state; void* recvmbox; void* acceptmbox; int /*<<< orphan*/  sem; TYPE_1__ pcb; } ;
struct api_msg {scalar_t__ err; int type; void (* callback ) (struct netconn*,int,u32) ;int /*<<< orphan*/  mbox; TYPE_4__ msg; scalar_t__ recvavail; scalar_t__ socket; int /*<<< orphan*/  state; void* recvmbox; void* acceptmbox; int /*<<< orphan*/  sem; TYPE_1__ pcb; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;
typedef  enum netconn_type { ____Placeholder_netconn_type } netconn_type ;

/* Variables and functions */
 int APIMSG_NEWCONN ; 
 scalar_t__ ERR_OK ; 
 int LWP_SemInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MEMP_NETCONN ; 
 int /*<<< orphan*/  MQBOX_SIZE ; 
 int /*<<< orphan*/  MQ_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ MQ_ERROR_SUCCESSFUL ; 
 scalar_t__ MQ_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_NONE ; 
 void* SYS_MBOX_NULL ; 
 int /*<<< orphan*/  apimsg_post (struct netconn*) ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct netconn*) ; 
 struct netconn* memp_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netconn* netconn_new_with_proto_and_callback(enum netconn_type t,u16 proto,void (*cb)(struct netconn *,enum netconn_evt,u32))
{
	u32 dummy = 0;
	struct netconn *conn;
	struct api_msg *msg;

	conn = memp_malloc(MEMP_NETCONN);
	if(!conn) return NULL;

	conn->err = ERR_OK;
	conn->type = t;
	conn->pcb.tcp = NULL;

	if(MQ_Init(&conn->mbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) {
		memp_free(MEMP_NETCONN,conn);
		return NULL;
	}
	if(LWP_SemInit(&conn->sem,0,1)==-1) {
		MQ_Close(conn->mbox);
		memp_free(MEMP_NETCONN,conn);
		return NULL;
	}

	conn->acceptmbox = SYS_MBOX_NULL;
	conn->recvmbox = SYS_MBOX_NULL;
	conn->state = NETCONN_NONE;
	conn->socket = 0;
	conn->callback = cb;
	conn->recvavail = 0;

	msg = memp_malloc(MEMP_API_MSG);
	if(!msg) {
		MQ_Close(conn->mbox);
		memp_free(MEMP_NETCONN,conn);
		return NULL;
	}

	msg->type = APIMSG_NEWCONN;
	msg->msg.msg.bc.port = proto;
	msg->msg.conn = conn;
	apimsg_post(msg);
	MQ_Receive(conn->mbox,(mqmsg_t)&dummy,MQ_MSG_BLOCK);
	memp_free(MEMP_API_MSG,msg);

	if(conn->err!=ERR_OK) {
		MQ_Close(conn->mbox);
		memp_free(MEMP_NETCONN,conn);
		return NULL;
	}
	return conn;
}