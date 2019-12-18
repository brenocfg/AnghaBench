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

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* unresettable_controller ; 

__attribute__((used)) static int ctlr_is_hard_resettable(u32 board_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(unresettable_controller); i++)
		if (unresettable_controller[i] == board_id)
			return 0;
	return 1;
}