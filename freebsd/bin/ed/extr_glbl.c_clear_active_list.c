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
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
 scalar_t__ active_last ; 
 int /*<<< orphan*/ * active_list ; 
 scalar_t__ active_ndx ; 
 scalar_t__ active_ptr ; 
 scalar_t__ active_size ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
clear_active_list(void)
{
	SPL1();
	active_size = active_last = active_ptr = active_ndx = 0;
	free(active_list);
	active_list = NULL;
	SPL0();
}