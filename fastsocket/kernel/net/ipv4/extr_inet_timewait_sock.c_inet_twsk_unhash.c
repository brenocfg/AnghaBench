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
struct inet_timewait_sock {int /*<<< orphan*/  tw_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_nulls_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_nulls_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_nulls_node_init (int /*<<< orphan*/ *) ; 

int inet_twsk_unhash(struct inet_timewait_sock *tw)
{
	if (hlist_nulls_unhashed(&tw->tw_node))
		return 0;

	hlist_nulls_del_rcu(&tw->tw_node);
	sk_nulls_node_init(&tw->tw_node);
	return 1;
}