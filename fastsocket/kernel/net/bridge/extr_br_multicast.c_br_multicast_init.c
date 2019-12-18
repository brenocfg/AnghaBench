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
struct net_bridge {int hash_elasticity; int hash_max; int multicast_router; int multicast_last_member_count; int multicast_startup_query_count; int multicast_last_member_interval; int multicast_query_response_interval; int multicast_startup_query_interval; int multicast_query_interval; int multicast_querier_interval; int multicast_membership_interval; int /*<<< orphan*/  multicast_query_timer; int /*<<< orphan*/  multicast_querier_timer; int /*<<< orphan*/  multicast_router_timer; int /*<<< orphan*/  multicast_lock; scalar_t__ multicast_querier; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  br_mdb_init () ; 
 int /*<<< orphan*/  br_multicast_local_router_expired ; 
 int /*<<< orphan*/  br_multicast_querier_expired ; 
 int /*<<< orphan*/  br_multicast_query_expired ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void br_multicast_init(struct net_bridge *br)
{
	br->hash_elasticity = 4;
	br->hash_max = 512;

	br->multicast_router = 1;
	br->multicast_querier = 0;
	br->multicast_last_member_count = 2;
	br->multicast_startup_query_count = 2;

	br->multicast_last_member_interval = HZ;
	br->multicast_query_response_interval = 10 * HZ;
	br->multicast_startup_query_interval = 125 * HZ / 4;
	br->multicast_query_interval = 125 * HZ;
	br->multicast_querier_interval = 255 * HZ;
	br->multicast_membership_interval = 260 * HZ;

	spin_lock_init(&br->multicast_lock);
	setup_timer(&br->multicast_router_timer,
		    br_multicast_local_router_expired, 0);
	setup_timer(&br->multicast_querier_timer,
		    br_multicast_querier_expired, (unsigned long)br);
	setup_timer(&br->multicast_query_timer, br_multicast_query_expired,
		    (unsigned long)br);
	br_mdb_init();
}