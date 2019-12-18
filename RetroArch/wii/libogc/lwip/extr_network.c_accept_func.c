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
typedef  int /*<<< orphan*/  sys_mbox ;
struct tcp_pcb {int dummy; } ;
struct TYPE_2__ {struct tcp_pcb* tcp; } ;
struct netconn {int socket; scalar_t__ recvavail; int /*<<< orphan*/  (* callback ) (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  err; int /*<<< orphan*/  acceptmbox; TYPE_1__ pcb; int /*<<< orphan*/  type; int /*<<< orphan*/  mbox; int /*<<< orphan*/  recvmbox; int /*<<< orphan*/  sem; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_LIB_DEBUG ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int LWP_SemInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEMP_NETCONN ; 
 int /*<<< orphan*/  MQBOX_SIZE ; 
 int /*<<< orphan*/  MQ_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ MQ_ERROR_SUCCESSFUL ; 
 scalar_t__ MQ_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,struct netconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTRCVPLUS ; 
 int /*<<< orphan*/  NETCONN_TCP ; 
 int /*<<< orphan*/  SYS_MBOX_NULL ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct netconn*) ; 
 struct netconn* memp_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setuptcp (struct netconn*) ; 
 int /*<<< orphan*/  stub1 (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t accept_func(void *arg,struct tcp_pcb *newpcb,err_t err)
{
	sys_mbox mbox;
	struct netconn *newconn,*conn = (struct netconn*)arg;

	LWIP_DEBUGF(API_LIB_DEBUG, ("accept_func: %p %p %d\n",arg,newpcb,err));

	mbox = conn->acceptmbox;
	newconn = memp_malloc(MEMP_NETCONN);
	if(newconn==NULL) return ERR_MEM;

	if(MQ_Init(&newconn->recvmbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) {
		memp_free(MEMP_NETCONN,newconn);
		return ERR_MEM;
	}

	if(MQ_Init(&newconn->mbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) {
		MQ_Close(newconn->recvmbox);
		memp_free(MEMP_NETCONN,newconn);
		return ERR_MEM;
	}

	if(LWP_SemInit(&newconn->sem,0,1)==-1) {
		MQ_Close(newconn->recvmbox);
		MQ_Close(newconn->mbox);
		memp_free(MEMP_NETCONN,newconn);
		return ERR_MEM;
	}

	newconn->type = NETCONN_TCP;
	newconn->pcb.tcp = newpcb;
	setuptcp(newconn);

	newconn->acceptmbox = SYS_MBOX_NULL;
	newconn->err = err;

	if(conn->callback) {
		(*conn->callback)(conn,NETCONN_EVTRCVPLUS,0);
	}
	newconn->callback = conn->callback;
	newconn->socket = -1;
	newconn->recvavail = 0;

	MQ_Send(mbox,newconn,MQ_MSG_BLOCK);
	return ERR_OK;
}