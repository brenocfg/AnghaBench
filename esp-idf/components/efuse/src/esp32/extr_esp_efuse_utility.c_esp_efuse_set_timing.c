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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_CLK_REG ; 
 int /*<<< orphan*/  EFUSE_CLK_SEL0 ; 
 int /*<<< orphan*/  EFUSE_CLK_SEL1 ; 
 int /*<<< orphan*/  EFUSE_DAC_CLK_DIV ; 
 int /*<<< orphan*/  EFUSE_DAC_CONF_REG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int esp_clk_apb_freq () ; 

__attribute__((used)) static esp_err_t esp_efuse_set_timing(void)
{
    uint32_t apb_freq_mhz = esp_clk_apb_freq() / 1000000;
    uint32_t clk_sel0, clk_sel1, dac_clk_div;
    if (apb_freq_mhz <= 26) {
        clk_sel0 = 250;
        clk_sel1 = 255;
        dac_clk_div = 52;
    } else if (apb_freq_mhz <= 40) {
        clk_sel0 = 160;
        clk_sel1 = 255;
        dac_clk_div = 80;
    } else {
        clk_sel0 = 80;
        clk_sel1 = 128;
        dac_clk_div = 100;
    }
    REG_SET_FIELD(EFUSE_DAC_CONF_REG, EFUSE_DAC_CLK_DIV, dac_clk_div);
    REG_SET_FIELD(EFUSE_CLK_REG, EFUSE_CLK_SEL0, clk_sel0);
    REG_SET_FIELD(EFUSE_CLK_REG, EFUSE_CLK_SEL1, clk_sel1);
    return ESP_OK;
}