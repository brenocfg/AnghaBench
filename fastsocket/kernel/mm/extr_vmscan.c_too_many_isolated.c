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
struct zone {int dummy; } ;
struct scan_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_INACTIVE_ANON ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int /*<<< orphan*/  NR_ISOLATED_ANON ; 
 int /*<<< orphan*/  NR_ISOLATED_FILE ; 
 scalar_t__ current_is_kswapd () ; 
 int /*<<< orphan*/  global_reclaim (struct scan_control*) ; 
 unsigned long zone_page_state (struct zone*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int too_many_isolated(struct zone *zone, int file,
		struct scan_control *sc)
{
	unsigned long inactive, isolated;

	if (current_is_kswapd())
		return 0;

	if (!global_reclaim(sc))
		return 0;

	if (file) {
		inactive = zone_page_state(zone, NR_INACTIVE_FILE);
		isolated = zone_page_state(zone, NR_ISOLATED_FILE);
	} else {
		inactive = zone_page_state(zone, NR_INACTIVE_ANON);
		isolated = zone_page_state(zone, NR_ISOLATED_ANON);
	}

	return isolated > inactive;
}