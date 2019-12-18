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
struct falcon_board {int minor; scalar_t__ major; } ;
struct efx_nic {int dummy; } ;
typedef  enum efx_led_mode { ____Placeholder_efx_led_mode } efx_led_mode ;

/* Variables and functions */
 int EFX_LED_ON ; 
 int /*<<< orphan*/  SFE4003_LED_OFF ; 
 int /*<<< orphan*/  SFE4003_LED_ON ; 
 int /*<<< orphan*/  SFE4003_RED_LED_GPIO ; 
 struct falcon_board* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_txc_set_gpio_val (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfe4003_set_id_led(struct efx_nic *efx, enum efx_led_mode mode)
{
	struct falcon_board *board = falcon_board(efx);

	/* The LEDs were not wired to GPIOs before A3 */
	if (board->minor < 3 && board->major == 0)
		return;

	falcon_txc_set_gpio_val(
		efx, SFE4003_RED_LED_GPIO,
		(mode == EFX_LED_ON) ? SFE4003_LED_ON : SFE4003_LED_OFF);
}