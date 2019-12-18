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
typedef  enum vga_switcheroo_state { ____Placeholder_vga_switcheroo_state } vga_switcheroo_state ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_DSM_POWER ; 
 int NOUVEAU_DSM_POWER_SPEED ; 
 int NOUVEAU_DSM_POWER_STAMINA ; 
 int VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  nouveau_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nouveau_dsm_set_discrete_state(acpi_handle handle, enum vga_switcheroo_state state)
{
	int arg;
	if (state == VGA_SWITCHEROO_ON)
		arg = NOUVEAU_DSM_POWER_SPEED;
	else
		arg = NOUVEAU_DSM_POWER_STAMINA;
	nouveau_dsm(handle, NOUVEAU_DSM_POWER, arg, NULL);
	return 0;
}