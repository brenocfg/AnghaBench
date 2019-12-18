#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u16 ;
struct tcp_pcb {int dummy; } ;
struct pbuf {scalar_t__ tot_len; } ;
struct netconn {scalar_t__ recvmbox; int /*<<< orphan*/  (* callback ) (struct netconn*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  recvavail; int /*<<< orphan*/  err; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_MSG_DEBUG ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (scalar_t__,struct pbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTRCVPLUS ; 
 scalar_t__ SYS_MBOX_NULL ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  stub1 (struct netconn*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static err_t recv_tcp(void *arg,struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
	u16 len;
	struct netconn *conn = (struct netconn*)arg;

	LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: recv_tcp(%p,%p,%p,%d)\n",arg,pcb,p,err));

	if(conn==NULL) {
		pbuf_free(p);
		return ERR_VAL;
	}

	if(conn->recvmbox!=SYS_MBOX_NULL) {
		conn->err = err;
		if(p!=NULL) {
			len = p->tot_len;
			conn->recvavail += len;
		} else len = 0;

		if(conn->callback)
			(*conn->callback)(conn,NETCONN_EVTRCVPLUS,len);

		MQ_Send(conn->recvmbox,p,MQ_MSG_BLOCK);
	}
	return ERR_OK;
}