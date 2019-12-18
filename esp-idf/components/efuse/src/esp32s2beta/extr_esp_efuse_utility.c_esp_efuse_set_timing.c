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
 int /*<<< orphan*/  EFUSE_DAC_CLK_DIV ; 
 int /*<<< orphan*/  EFUSE_DAC_CONF_REG ; 
 int /*<<< orphan*/  EFUSE_PWR_ON_NUM ; 
 int /*<<< orphan*/  EFUSE_RD_TIM_CONF_REG ; 
 int /*<<< orphan*/  EFUSE_THP_A ; 
 int /*<<< orphan*/  EFUSE_THR_A ; 
 int /*<<< orphan*/  EFUSE_TPGM ; 
 int /*<<< orphan*/  EFUSE_TPGM_INACTIVE ; 
 int /*<<< orphan*/  EFUSE_TRD ; 
 int /*<<< orphan*/  EFUSE_TSUP_A ; 
 int /*<<< orphan*/  EFUSE_TSUR_A ; 
 int /*<<< orphan*/  EFUSE_WR_TIM_CONF0_REG ; 
 int /*<<< orphan*/  EFUSE_WR_TIM_CONF1_REG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TAG ; 
 int esp_clk_apb_freq () ; 

__attribute__((used)) static esp_err_t esp_efuse_set_timing(void)
{
    uint32_t clock = esp_clk_apb_freq();
    // ets_efuse_set_timing(clock);
    uint32_t clk_div, power_on; 
    //uint32_t power_off; // Support for 7.2.3 chip
    uint32_t tsup_a = 1, thp_a = 1, tpgm, tpgm_inact;
    uint32_t tsur_a = 1, thr_a = 1, trd;
    if (clock == 20000000 || clock == 5000000 || clock == 10000000) {
        clk_div = 0x28;
        power_on = 0x2880;
        //power_off = 0x40;
        tpgm = 0xc8;
        tpgm_inact = 1;
        trd = 1;
    } else if (clock == 40000000) {
        clk_div = 0x50;
        power_on = 0x5100;
        //power_off = 0x80;
        tpgm = 0x190;
        tpgm_inact = 2;
        trd = 2;
    } else  if (clock == 80000000) {
        clk_div = 0xa0;
        power_on = 0xa200;
        //power_off = 0x100;
        tpgm = 0x320;
        tpgm_inact = 3;
        trd = 3;
    } else {
        ESP_LOGE(TAG, "Efuse does not support this %d Hz APB clock", clock);
        return ESP_ERR_NOT_SUPPORTED;
    }
    REG_SET_FIELD(EFUSE_DAC_CONF_REG, EFUSE_DAC_CLK_DIV, clk_div);
    REG_SET_FIELD(EFUSE_WR_TIM_CONF0_REG, EFUSE_TPGM, tpgm);
    REG_SET_FIELD(EFUSE_WR_TIM_CONF0_REG, EFUSE_TPGM_INACTIVE, tpgm_inact);
    REG_SET_FIELD(EFUSE_WR_TIM_CONF0_REG, EFUSE_THP_A, thp_a);
    REG_SET_FIELD(EFUSE_WR_TIM_CONF1_REG, EFUSE_PWR_ON_NUM, power_on);
    REG_SET_FIELD(EFUSE_WR_TIM_CONF1_REG, EFUSE_TSUP_A, tsup_a);
    //REG_SET_FIELD(EFUSE_WR_TIM_CONF2_REG, EFUSE_PWR_OFF_NUM, power_off);
    REG_SET_FIELD(EFUSE_RD_TIM_CONF_REG, EFUSE_TSUR_A, tsur_a);
    REG_SET_FIELD(EFUSE_RD_TIM_CONF_REG, EFUSE_TRD, trd);
    REG_SET_FIELD(EFUSE_RD_TIM_CONF_REG, EFUSE_THR_A, thr_a);
    return ESP_OK;
}