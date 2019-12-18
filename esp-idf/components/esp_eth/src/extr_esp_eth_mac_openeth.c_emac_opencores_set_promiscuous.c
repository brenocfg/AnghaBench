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
typedef  int /*<<< orphan*/  esp_eth_mac_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  OPENETH_MODER_REG ; 
 int /*<<< orphan*/  OPENETH_PRO ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t emac_opencores_set_promiscuous(esp_eth_mac_t *mac, bool enable)
{
    if (enable) {
        REG_SET_BIT(OPENETH_MODER_REG, OPENETH_PRO);
    } else {
        REG_CLR_BIT(OPENETH_MODER_REG, OPENETH_PRO);
    }
    return ESP_OK;
}