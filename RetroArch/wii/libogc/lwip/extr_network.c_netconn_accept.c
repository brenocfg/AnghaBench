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
struct netconn {int /*<<< orphan*/  (* callback ) (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  acceptmbox; } ;
typedef  int /*<<< orphan*/  mqmsg_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_LIB_DEBUG ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETCONN_EVTRCVMINUS ; 
 int /*<<< orphan*/  stub1 (struct netconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netconn* netconn_accept(struct netconn* conn)
{
	struct netconn *newconn;

	if(conn==NULL) return NULL;

	LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_accept(%p)\n", conn));
	MQ_Receive(conn->acceptmbox,(mqmsg_t)&newconn,MQ_MSG_BLOCK);
	if(conn->callback)
		(*conn->callback)(conn,NETCONN_EVTRCVMINUS,0);

	return newconn;
}