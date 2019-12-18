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
struct rpc_clnt {int /*<<< orphan*/  cl_count; int /*<<< orphan*/  cl_tasks; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_wait ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_clnt*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_free_auth (struct rpc_clnt*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void
rpc_release_client(struct rpc_clnt *clnt)
{
	dprintk("RPC:       rpc_release_client(%p)\n", clnt);

	if (list_empty(&clnt->cl_tasks))
		wake_up(&destroy_wait);
	if (atomic_dec_and_test(&clnt->cl_count))
		rpc_free_auth(clnt);
}