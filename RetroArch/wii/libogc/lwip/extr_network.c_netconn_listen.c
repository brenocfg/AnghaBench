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
struct netconn {scalar_t__ acceptmbox; int err; int /*<<< orphan*/  mbox; } ;
struct TYPE_2__ {struct netconn* conn; } ;
struct api_msg {TYPE_1__ msg; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;
typedef  int err_t ;

/* Variables and functions */
 int /*<<< orphan*/  APIMSG_LISTEN ; 
 int /*<<< orphan*/  API_LIB_DEBUG ; 
 int ERR_MEM ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MQBOX_SIZE ; 
 scalar_t__ MQ_ERROR_SUCCESSFUL ; 
 scalar_t__ MQ_Init (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_MBOX_NULL ; 
 int /*<<< orphan*/  apimsg_post (struct api_msg*) ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct api_msg*) ; 
 struct api_msg* memp_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t netconn_listen(struct netconn *conn)
{
	u32 dummy = 0;
	struct api_msg *msg;

	LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_listen(%p)\n", conn));

	if(conn==NULL) return -1;
	if(conn->acceptmbox==SYS_MBOX_NULL) {
		if(MQ_Init(&conn->acceptmbox,MQBOX_SIZE)!=MQ_ERROR_SUCCESSFUL) return ERR_MEM;
	}

	if((msg=memp_malloc(MEMP_API_MSG))==NULL) return (conn->err = ERR_MEM);
	msg->type = APIMSG_LISTEN;
	msg->msg.conn = conn;
	apimsg_post(msg);
	MQ_Receive(conn->mbox,(mqmsg_t)&dummy,MQ_MSG_BLOCK);
	memp_free(MEMP_API_MSG,msg);
	return conn->err;
}