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
typedef  scalar_t__ u32 ;
struct clocksource {int dummy; } ;
typedef  scalar_t__ cycle_t ;

/* Variables and functions */
 scalar_t__ MTU_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ mtu_base ; 
 scalar_t__ nmdk_count ; 
 scalar_t__ nmdk_cycle ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static cycle_t nmdk_read_timer(struct clocksource *cs)
{
	u32 count = readl(mtu_base + MTU_VAL(0));
	return nmdk_count + nmdk_cycle - count;

}