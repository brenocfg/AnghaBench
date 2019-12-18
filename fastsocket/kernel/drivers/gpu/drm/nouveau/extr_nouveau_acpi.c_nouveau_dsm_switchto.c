#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_2__ {int /*<<< orphan*/  dhandle; int /*<<< orphan*/  dsm_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_DSM_LED_SPEED ; 
 int /*<<< orphan*/  NOUVEAU_DSM_LED_STAMINA ; 
 int VGA_SWITCHEROO_IGD ; 
 TYPE_1__ nouveau_dsm_priv ; 
 int nouveau_dsm_switch_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nouveau_dsm_switchto(enum vga_switcheroo_client_id id)
{
	if (!nouveau_dsm_priv.dsm_detected)
		return 0;
	if (id == VGA_SWITCHEROO_IGD)
		return nouveau_dsm_switch_mux(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_LED_STAMINA);
	else
		return nouveau_dsm_switch_mux(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_LED_SPEED);
}