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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mp_PM_func () ; 

__attribute__((used)) static void
mp_call_PM(void)
{
	assert(!ml_get_interrupts_enabled());

	if (mp_PM_func != NULL)
		mp_PM_func();
}