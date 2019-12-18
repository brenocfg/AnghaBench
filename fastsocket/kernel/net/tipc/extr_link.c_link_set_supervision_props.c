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
typedef  int u32 ;
struct link {int tolerance; int continuity_interval; int abort_limit; } ;

/* Variables and functions */

__attribute__((used)) static void link_set_supervision_props(struct link *l_ptr, u32 tolerance)
{
	l_ptr->tolerance = tolerance;
	l_ptr->continuity_interval =
		((tolerance / 4) > 500) ? 500 : tolerance / 4;
	l_ptr->abort_limit = tolerance / (l_ptr->continuity_interval / 4);
}