#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct netconn {scalar_t__ type; scalar_t__ recvmbox; int /*<<< orphan*/  err; int /*<<< orphan*/  mbox; } ;
struct ip_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; struct ip_addr* ipaddr; } ;
struct TYPE_5__ {TYPE_1__ bc; } ;
struct TYPE_6__ {TYPE_2__ msg; struct netconn* conn; } ;
struct api_msg {TYPE_3__ msg; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  APIMSG_BIND ; 
 int /*<<< orphan*/  API_LIB_DEBUG ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MQBOX_SIZE ; 
 scalar_t__ MQ_ERROR_SUCCESSFUL ; 
 scalar_t__ MQ_Init (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NETCONN_TCP ; 
 scalar_t__ SYS_MBOX_NULL ; 
 int /*<<< orphan*/  apimsg_post (struct api_msg*) ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct api_msg*) ; 
 struct api_msg* memp_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t netconn_bind(struct netconn *conn,struct ip_addr *addr,u16 port)
{
	u32 dummy = 0;
	struct api_msg *msg;

	LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_bind(%p)\n", conn));

	if(conn==NULL) return ERR_VAL;
	if(conn->type!=NETCONN_TCP && conn->recvmbox==SYS_MBOX_NULL) {
		if(MQ_Init(&conn->recvmbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) return ERR_MEM;
	}

	if((msg=memp_malloc(MEMP_API_MSG))==NULL)
		return (conn->err = ERR_MEM);

	msg->type = APIMSG_BIND;
	msg->msg.conn = conn;
	msg->msg.msg.bc.ipaddr = addr;
	msg->msg.msg.bc.port = port;
	apimsg_post(msg);
	MQ_Receive(conn->mbox,(mqmsg_t)&dummy,MQ_MSG_BLOCK);
	memp_free(MEMP_API_MSG,msg);
	return conn->err;
}