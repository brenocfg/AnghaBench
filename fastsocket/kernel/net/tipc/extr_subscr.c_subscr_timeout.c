#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
struct TYPE_6__ {TYPE_1__ seq; } ;
struct TYPE_7__ {TYPE_2__ s; } ;
struct subscription {scalar_t__ timeout; int /*<<< orphan*/  timer; TYPE_3__ evt; int /*<<< orphan*/  subscription_list; int /*<<< orphan*/  server_ref; } ;
struct port {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  subscription_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_SUBSCR_TIMEOUT ; 
 scalar_t__ TIPC_WAIT_FOREVER ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_term_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct subscription*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subscr_send_event (struct subscription*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nametbl_unsubscribe (struct subscription*) ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 
 TYPE_4__ topsrv ; 

__attribute__((used)) static void subscr_timeout(struct subscription *sub)
{
	struct port *server_port;

	/* Validate server port reference (in case subscriber is terminating) */

	server_port = tipc_port_lock(sub->server_ref);
	if (server_port == NULL)
		return;

	/* Validate timeout (in case subscription is being cancelled) */

	if (sub->timeout == TIPC_WAIT_FOREVER) {
		tipc_port_unlock(server_port);
		return;
	}

	/* Unlink subscription from name table */

	tipc_nametbl_unsubscribe(sub);

	/* Unlink subscription from subscriber */

	list_del(&sub->subscription_list);

	/* Release subscriber's server port */

	tipc_port_unlock(server_port);

	/* Notify subscriber of timeout */

	subscr_send_event(sub, sub->evt.s.seq.lower, sub->evt.s.seq.upper,
			  TIPC_SUBSCR_TIMEOUT, 0, 0);

	/* Now destroy subscription */

	k_term_timer(&sub->timer);
	kfree(sub);
	atomic_dec(&topsrv.subscription_count);
}