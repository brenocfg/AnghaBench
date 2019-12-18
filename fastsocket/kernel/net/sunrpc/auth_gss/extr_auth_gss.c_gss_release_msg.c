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
struct gss_upcall_msg {int /*<<< orphan*/  rpc_waitqueue; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  list; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_put_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gss_upcall_msg*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pipe_version () ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gss_release_msg(struct gss_upcall_msg *gss_msg)
{
	if (!atomic_dec_and_test(&gss_msg->count))
		return;
	put_pipe_version();
	BUG_ON(!list_empty(&gss_msg->list));
	if (gss_msg->ctx != NULL)
		gss_put_ctx(gss_msg->ctx);
	rpc_destroy_wait_queue(&gss_msg->rpc_waitqueue);
	kfree(gss_msg);
}