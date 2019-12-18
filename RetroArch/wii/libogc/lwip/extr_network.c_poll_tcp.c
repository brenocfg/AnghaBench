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
struct tcp_pcb {int dummy; } ;
struct netconn {scalar_t__ sem; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  API_MSG_DEBUG ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWP_SemPost (scalar_t__) ; 
 scalar_t__ NETCONN_CLOSE ; 
 scalar_t__ NETCONN_WRITE ; 
 scalar_t__ SYS_SEM_NULL ; 

__attribute__((used)) static err_t poll_tcp(void *arg,struct tcp_pcb *pcb)
{
	struct netconn *conn = (struct netconn*)arg;

	LWIP_DEBUGF(API_MSG_DEBUG, ("api_msg: poll_tcp\n"));
	if(conn && conn->sem!=SYS_SEM_NULL && (conn->state==NETCONN_WRITE || conn->state==NETCONN_CLOSE))
		LWP_SemPost(conn->sem);

	return ERR_OK;
}