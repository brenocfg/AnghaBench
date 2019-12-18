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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * tcp; } ;
struct netconn {scalar_t__ recvmbox; scalar_t__ mbox; scalar_t__ acceptmbox; scalar_t__ sem; int /*<<< orphan*/  (* callback ) (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ pcb; int /*<<< orphan*/  err; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_MSG_DEBUG ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_SemPost (scalar_t__) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTRCVPLUS ; 
 scalar_t__ SYS_MBOX_NULL ; 
 scalar_t__ SYS_SEM_NULL ; 
 int /*<<< orphan*/  stub1 (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void err_tcp(void *arg,err_t err)
{
	u32 dummy = 0;
	struct netconn *conn = (struct netconn*)arg;

	LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: err_tcp: %d\n",err));
	if(conn) {
		conn->err = err;
		conn->pcb.tcp = NULL;
		if(conn->recvmbox!=SYS_MBOX_NULL) {
			if(conn->callback) (*conn->callback)(conn,NETCONN_EVTRCVPLUS,0);
			MQ_Send(conn->recvmbox,&dummy,MQ_MSG_BLOCK);
		}
		if(conn->mbox!=SYS_MBOX_NULL) {
			MQ_Send(conn->mbox,&dummy,MQ_MSG_BLOCK);
		}
		if(conn->acceptmbox!=SYS_MBOX_NULL) {
			if(conn->callback) (*conn->callback)(conn,NETCONN_EVTRCVPLUS,0);
			MQ_Send(conn->acceptmbox,&dummy,MQ_MSG_BLOCK);
		}
		if(conn->sem!=SYS_SEM_NULL) {
			LWP_SemPost(conn->sem);
		}
	}
}