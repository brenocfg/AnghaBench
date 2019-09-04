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
typedef  int /*<<< orphan*/  pal_cr_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_cr0 () ; 
 int /*<<< orphan*/  get_cr2 () ; 
 int /*<<< orphan*/  get_cr3_raw () ; 
 int /*<<< orphan*/  get_cr4 () ; 

void
pal_get_control_registers( pal_cr_t *cr0, pal_cr_t *cr2, 
			   pal_cr_t *cr3, pal_cr_t *cr4 )
{
	*cr0 = get_cr0();
	*cr2 = get_cr2();
	*cr3 = get_cr3_raw();
	*cr4 = get_cr4();
}