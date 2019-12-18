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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int QUAKE_LED_LINK_ACT ; 
 int QUAKE_LED_LINK_STAT ; 
 int QUAKE_LED_RXLINK ; 
 int /*<<< orphan*/  SFN4112F_ACT_LED ; 
 int /*<<< orphan*/  SFN4112F_LINK_LED ; 
 int /*<<< orphan*/  falcon_qt202x_set_led (struct efx_nic*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sfn4112f_init_phy(struct efx_nic *efx)
{
	falcon_qt202x_set_led(efx, SFN4112F_ACT_LED,
			      QUAKE_LED_RXLINK | QUAKE_LED_LINK_ACT);
	falcon_qt202x_set_led(efx, SFN4112F_LINK_LED,
			      QUAKE_LED_RXLINK | QUAKE_LED_LINK_STAT);
}