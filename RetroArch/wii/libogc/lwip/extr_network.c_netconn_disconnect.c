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
struct netconn {int /*<<< orphan*/  err; int /*<<< orphan*/  mbox; } ;
struct TYPE_2__ {struct netconn* conn; } ;
struct api_msg {TYPE_1__ msg; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  APIMSG_DISCONNECT ; 
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apimsg_post (struct api_msg*) ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct api_msg*) ; 
 struct api_msg* memp_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t netconn_disconnect(struct netconn *conn)
{
	u32 dummy = 0;
	struct api_msg *msg;

	if(conn==NULL) return ERR_VAL;
	if((msg=memp_malloc(MEMP_API_MSG))==NULL) return ERR_MEM;

	msg->type = APIMSG_DISCONNECT;
	msg->msg.conn = conn;
	apimsg_post(msg);
	MQ_Receive(conn->mbox,(mqmsg_t)&dummy,MQ_MSG_BLOCK);
	memp_free(MEMP_API_MSG,msg);
	return conn->err;
}