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
struct TYPE_2__ {int /*<<< orphan*/  errno; } ;
struct gss_upcall_msg {int /*<<< orphan*/  count; int /*<<< orphan*/  waitqueue; TYPE_1__ msg; int /*<<< orphan*/  rpc_waitqueue; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__gss_unhash_msg(struct gss_upcall_msg *gss_msg)
{
	list_del_init(&gss_msg->list);
	rpc_wake_up_status(&gss_msg->rpc_waitqueue, gss_msg->msg.errno);
	wake_up_all(&gss_msg->waitqueue);
	atomic_dec(&gss_msg->count);
}