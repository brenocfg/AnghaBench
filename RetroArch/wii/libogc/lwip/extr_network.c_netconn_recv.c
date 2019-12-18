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
typedef  int u16 ;
struct pbuf {int tot_len; } ;
struct TYPE_6__ {TYPE_1__* tcp; } ;
struct netconn {scalar_t__ recvmbox; scalar_t__ type; scalar_t__ mbox; void* err; int /*<<< orphan*/  (* callback ) (struct netconn*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  recvavail; TYPE_2__ pcb; } ;
struct TYPE_7__ {int len; } ;
struct TYPE_8__ {TYPE_3__ msg; struct netconn* conn; } ;
struct netbuf {struct pbuf* p; TYPE_4__ msg; int /*<<< orphan*/  type; int /*<<< orphan*/ * fromaddr; scalar_t__ fromport; struct pbuf* ptr; } ;
struct api_msg {struct pbuf* p; TYPE_4__ msg; int /*<<< orphan*/  type; int /*<<< orphan*/ * fromaddr; scalar_t__ fromport; struct pbuf* ptr; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIMSG_RECV ; 
 int /*<<< orphan*/  API_LIB_DEBUG ; 
 void* ERR_CONN ; 
 void* ERR_MEM ; 
 void* ERR_OK ; 
 scalar_t__ LISTEN ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MEMP_NETBUF ; 
 int /*<<< orphan*/  MQ_Close (scalar_t__) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTRCVMINUS ; 
 scalar_t__ NETCONN_TCP ; 
 scalar_t__ SYS_MBOX_NULL ; 
 int /*<<< orphan*/  apimsg_post (struct netbuf*) ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct netbuf*) ; 
 struct netbuf* memp_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct netconn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct netconn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct netbuf* netconn_recv(struct netconn *conn)
{
	u32 dummy = 0;
	struct api_msg *msg;
	struct netbuf *buf;
	struct pbuf *p;
	u16 len;

	if(conn==NULL) return NULL;
	if(conn->recvmbox==SYS_MBOX_NULL) {
		conn->err = ERR_CONN;
		return NULL;
	}
	if(conn->err!=ERR_OK) return NULL;

	if(conn->type==NETCONN_TCP) {
		if(conn->pcb.tcp->state==LISTEN) {
			conn->err = ERR_CONN;
			return NULL;
		}

		buf = memp_malloc(MEMP_NETBUF);
		if(buf==NULL) {
			conn->err = ERR_MEM;
			return NULL;
		}

		MQ_Receive(conn->recvmbox,(mqmsg_t)&p,MQ_MSG_BLOCK);
		if(p!=NULL) {
			len = p->tot_len;
			conn->recvavail -= len;
		} else
			len = 0;

		if(conn->callback)
			(*conn->callback)(conn,NETCONN_EVTRCVMINUS,len);

		if(p==NULL) {
			memp_free(MEMP_NETBUF,buf);
			MQ_Close(conn->recvmbox);
			conn->recvmbox = SYS_MBOX_NULL;
			return NULL;
		}

		buf->p = p;
		buf->ptr = p;
		buf->fromport = 0;
		buf->fromaddr = NULL;

		if((msg=memp_malloc(MEMP_API_MSG))==NULL) {
			conn->err = ERR_MEM;
			return buf;
		}

		msg->type = APIMSG_RECV;
		msg->msg.conn = conn;
		if(buf!=NULL)
			msg->msg.msg.len = len;
		else
			msg->msg.msg.len = 1;

		apimsg_post(msg);
		MQ_Receive(conn->mbox,(mqmsg_t)&dummy,MQ_MSG_BLOCK);
		memp_free(MEMP_API_MSG,msg);
	} else {
		MQ_Receive(conn->recvmbox,(mqmsg_t)&buf,MQ_MSG_BLOCK);
		conn->recvavail -= buf->p->tot_len;
		if(conn->callback)
			(*conn->callback)(conn,NETCONN_EVTRCVMINUS,buf->p->tot_len);
	}

	LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_recv: received %p (err %d)\n", (void *)buf, conn->err));
	return buf;
}