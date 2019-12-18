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
 unsigned long curr_ticks ; 
 int /*<<< orphan*/  opened ; 

__attribute__((used)) static unsigned long
def_tmr_get_time(int dev)
{
	if (!opened)
		return 0;

	return curr_ticks;
}