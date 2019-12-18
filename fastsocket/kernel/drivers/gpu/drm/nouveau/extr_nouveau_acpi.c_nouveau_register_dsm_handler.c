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
 int nouveau_dsm_detect () ; 
 int /*<<< orphan*/  nouveau_dsm_handler ; 
 int /*<<< orphan*/  vga_switcheroo_register_handler (int /*<<< orphan*/ *) ; 

void nouveau_register_dsm_handler(void)
{
	bool r;

	r = nouveau_dsm_detect();
	if (!r)
		return;

	vga_switcheroo_register_handler(&nouveau_dsm_handler);
}