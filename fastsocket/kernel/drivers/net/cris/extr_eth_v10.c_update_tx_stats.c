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
struct net_device_stats {int /*<<< orphan*/  collisions; } ;

/* Variables and functions */
 scalar_t__ IO_EXTRACT (unsigned long*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long* R_TR_COUNTERS ; 
 int /*<<< orphan*/  multiple_col ; 
 int /*<<< orphan*/  single_col ; 

__attribute__((used)) static void
update_tx_stats(struct net_device_stats *es)
{
	unsigned long r = *R_TR_COUNTERS;
	/* update stats relevant to transmission errors */
	es->collisions +=
		IO_EXTRACT(R_TR_COUNTERS, single_col, r) +
		IO_EXTRACT(R_TR_COUNTERS, multiple_col, r);
}