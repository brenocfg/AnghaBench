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

/* Variables and functions */
 int /*<<< orphan*/  SFE4003_LED_OFF ; 
 int /*<<< orphan*/  SFE4003_RED_LED_GPIO ; 
 int /*<<< orphan*/  TXC_GPIO_DIR_OUTPUT ; 
 struct falcon_board* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_txc_set_gpio_dir (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_txc_set_gpio_val (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfe4003_init_phy(struct efx_nic *efx)
{
	struct falcon_board *board = falcon_board(efx);

	/* The LEDs were not wired to GPIOs before A3 */
	if (board->minor < 3 && board->major == 0)
		return;

	falcon_txc_set_gpio_dir(efx, SFE4003_RED_LED_GPIO, TXC_GPIO_DIR_OUTPUT);
	falcon_txc_set_gpio_val(efx, SFE4003_RED_LED_GPIO, SFE4003_LED_OFF);
}