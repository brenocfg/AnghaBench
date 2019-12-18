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

/* Variables and functions */
 scalar_t__ CABLE_OVERRIDE_DISABLED ; 
 scalar_t__ cable_selection_override ; 

__attribute__((used)) static inline int is_cable_select_overridden(void)
{
	return cable_selection_override < CABLE_OVERRIDE_DISABLED;
}