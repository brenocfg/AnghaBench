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
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_base ; 
 int /*<<< orphan*/  kernel_end ; 
 int /*<<< orphan*/  kernel_items ; 
 int /*<<< orphan*/  redset ; 
 int /*<<< orphan*/  shift_symbol ; 
 int /*<<< orphan*/  shiftset ; 
 int /*<<< orphan*/  state_set ; 

__attribute__((used)) static void
free_storage(void)
{
    FREE(shift_symbol);
    FREE(redset);
    FREE(shiftset);
    FREE(kernel_base);
    FREE(kernel_end);
    FREE(kernel_items);
    FREE(state_set);
}