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

/* Variables and functions */
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 unsigned long zone_page_state (struct zone*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inactive_file_is_low_global(struct zone *zone)
{
	unsigned long active, inactive;

	active = zone_page_state(zone, NR_ACTIVE_FILE);
	inactive = zone_page_state(zone, NR_INACTIVE_FILE);

	return (active > inactive);
}