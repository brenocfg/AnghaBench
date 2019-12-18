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
struct net_bridge {scalar_t__ multicast_startup_queries_sent; scalar_t__ multicast_startup_query_count; int /*<<< orphan*/  multicast_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_send_query (struct net_bridge*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_query_expired(unsigned long data)
{
	struct net_bridge *br = (void *)data;

	spin_lock(&br->multicast_lock);
	if (br->multicast_startup_queries_sent <
	    br->multicast_startup_query_count)
		br->multicast_startup_queries_sent++;

	br_multicast_send_query(br, NULL, br->multicast_startup_queries_sent);

	spin_unlock(&br->multicast_lock);
}