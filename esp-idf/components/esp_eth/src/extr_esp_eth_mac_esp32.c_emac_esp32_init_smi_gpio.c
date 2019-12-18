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
 size_t CONFIG_ETH_SMI_MDC_GPIO ; 
 size_t CONFIG_ETH_SMI_MDIO_GPIO ; 
 int /*<<< orphan*/  EMAC_MDC_O_IDX ; 
 int /*<<< orphan*/  EMAC_MDI_I_IDX ; 
 int /*<<< orphan*/  EMAC_MDO_O_IDX ; 
 int /*<<< orphan*/  GPIO_MODE_INPUT_OUTPUT ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/ * GPIO_PIN_MUX_REG ; 
 int /*<<< orphan*/  PIN_FUNC_GPIO ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_matrix_in (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_matrix_out (size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gpio_set_direction (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emac_esp32_init_smi_gpio(void)
{
    /* Setup SMI MDC GPIO */
    gpio_set_direction(CONFIG_ETH_SMI_MDC_GPIO, GPIO_MODE_OUTPUT);
    gpio_matrix_out(CONFIG_ETH_SMI_MDC_GPIO, EMAC_MDC_O_IDX, false, false);
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[CONFIG_ETH_SMI_MDC_GPIO], PIN_FUNC_GPIO);
    /* Setup SMI MDIO GPIO */
    gpio_set_direction(CONFIG_ETH_SMI_MDIO_GPIO, GPIO_MODE_INPUT_OUTPUT);
    gpio_matrix_out(CONFIG_ETH_SMI_MDIO_GPIO, EMAC_MDO_O_IDX, false, false);
    gpio_matrix_in(CONFIG_ETH_SMI_MDIO_GPIO, EMAC_MDI_I_IDX, false);
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[CONFIG_ETH_SMI_MDIO_GPIO], PIN_FUNC_GPIO);
}