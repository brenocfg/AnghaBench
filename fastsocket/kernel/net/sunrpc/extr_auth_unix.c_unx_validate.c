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
typedef  int u32 ;
struct rpc_task {TYPE_3__* tk_rqstp; } ;
typedef  scalar_t__ rpc_authflavor_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {TYPE_2__* rq_cred; } ;
struct TYPE_5__ {TYPE_1__* cr_auth; } ;
struct TYPE_4__ {int au_rslack; } ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_NULL ; 
 scalar_t__ RPC_AUTH_SHORT ; 
 scalar_t__ RPC_AUTH_UNIX ; 
 int RPC_MAX_AUTH_SIZE ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static __be32 *
unx_validate(struct rpc_task *task, __be32 *p)
{
	rpc_authflavor_t	flavor;
	u32			size;

	flavor = ntohl(*p++);
	if (flavor != RPC_AUTH_NULL &&
	    flavor != RPC_AUTH_UNIX &&
	    flavor != RPC_AUTH_SHORT) {
		printk("RPC: bad verf flavor: %u\n", flavor);
		return NULL;
	}

	size = ntohl(*p++);
	if (size > RPC_MAX_AUTH_SIZE) {
		printk("RPC: giant verf size: %u\n", size);
		return NULL;
	}
	task->tk_rqstp->rq_cred->cr_auth->au_rslack = (size >> 2) + 2;
	p += (size >> 2);

	return p;
}