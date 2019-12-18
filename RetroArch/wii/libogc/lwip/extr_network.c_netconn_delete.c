#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ sys_mbox ;
struct pbuf {int dummy; } ;
struct TYPE_2__ {struct netconn* conn; } ;
struct netconn {scalar_t__ type; scalar_t__ mbox; scalar_t__ recvmbox; scalar_t__ acceptmbox; int /*<<< orphan*/  sem; TYPE_1__ msg; } ;
struct netbuf {int dummy; } ;
struct api_msg {scalar_t__ type; scalar_t__ mbox; scalar_t__ recvmbox; scalar_t__ acceptmbox; int /*<<< orphan*/  sem; TYPE_1__ msg; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 scalar_t__ APIMSG_DELCONN ; 
 int /*<<< orphan*/  API_LIB_DEBUG ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_SemDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MEMP_NETCONN ; 
 int /*<<< orphan*/  MQ_Close (scalar_t__) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_MSG_NOBLOCK ; 
 scalar_t__ MQ_Receive (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NETCONN_TCP ; 
 scalar_t__ SYS_MBOX_NULL ; 
 int /*<<< orphan*/  SYS_SEM_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  apimsg_post (struct netconn*) ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct netconn*) ; 
 struct netconn* memp_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netbuf_delete (struct netbuf*) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

__attribute__((used)) static err_t netconn_delete(struct netconn *conn)
{
	u32 dummy = 0;
	struct api_msg *msg;
	sys_mbox mbox;
	void *mem;

	LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_delete(%p)\n", conn));

	if(!conn) return ERR_OK;

	msg = memp_malloc(MEMP_API_MSG);
	if(!msg) return ERR_MEM;

	msg->type = APIMSG_DELCONN;
	msg->msg.conn = conn;
	apimsg_post(msg);
	MQ_Receive(conn->mbox,(mqmsg_t)&dummy,MQ_MSG_BLOCK);
	memp_free(MEMP_API_MSG,msg);

	mbox = conn->recvmbox;
	conn->recvmbox = SYS_MBOX_NULL;
	if(mbox!=SYS_MBOX_NULL) {
		while(MQ_Receive(mbox,(mqmsg_t)&mem,MQ_MSG_NOBLOCK)==TRUE) {
			if(mem!=NULL) {
				if(conn->type==NETCONN_TCP)
					pbuf_free((struct pbuf*)mem);
				else
					netbuf_delete((struct netbuf*)mem);
			}
		}
		MQ_Close(mbox);
	}

	mbox = conn->acceptmbox;
	conn->acceptmbox = SYS_MBOX_NULL;
	if(mbox!=SYS_MBOX_NULL) {
		while(MQ_Receive(mbox,(mqmsg_t)&mem,MQ_MSG_NOBLOCK)==TRUE) {
			if(mem!=NULL) netconn_delete((struct netconn*)mem);
		}
		MQ_Close(mbox);
	}

	MQ_Close(conn->mbox);
	conn->mbox = SYS_MBOX_NULL;

	LWP_SemDestroy(conn->sem);
	conn->sem = SYS_SEM_NULL;

	memp_free(MEMP_NETCONN,conn);
	return ERR_OK;
}