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
 int /*<<< orphan*/  _go32_dpmi_set_protected_mode_interrupt_vector (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_key_handler ; 

void key_done(void)
{
	_go32_dpmi_set_protected_mode_interrupt_vector(0x9, &old_key_handler);
}