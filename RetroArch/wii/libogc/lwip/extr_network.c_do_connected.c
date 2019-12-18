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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_pcb {int dummy; } ;
struct netconn {scalar_t__ type; int /*<<< orphan*/  mbox; scalar_t__ err; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 scalar_t__ ERR_VAL ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NETCONN_TCP ; 
 int /*<<< orphan*/  setuptcp (struct netconn*) ; 

__attribute__((used)) static err_t do_connected(void *arg,struct tcp_pcb *pcb,err_t err)
{
	u32 dummy = 0;
	struct netconn *conn = (struct netconn*)arg;

	if(!conn) return ERR_VAL;

	conn->err = err;
	if(conn->type==NETCONN_TCP && err==ERR_OK) setuptcp(conn);

	MQ_Send(conn->mbox,&dummy,MQ_MSG_BLOCK);
	return ERR_OK;
}