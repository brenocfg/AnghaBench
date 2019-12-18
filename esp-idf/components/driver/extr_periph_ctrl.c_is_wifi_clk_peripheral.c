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
typedef  int periph_module_t ;

/* Variables and functions */
#define  PERIPH_BT_BASEBAND_MODULE 136 
#define  PERIPH_BT_LC_MODULE 135 
#define  PERIPH_BT_MODULE 134 
#define  PERIPH_EMAC_MODULE 133 
#define  PERIPH_RNG_MODULE 132 
#define  PERIPH_SDIO_SLAVE_MODULE 131 
#define  PERIPH_SDMMC_MODULE 130 
#define  PERIPH_WIFI_BT_COMMON_MODULE 129 
#define  PERIPH_WIFI_MODULE 128 

__attribute__((used)) static bool is_wifi_clk_peripheral(periph_module_t periph)
{
    /* A small subset of peripherals use WIFI_CLK_EN_REG and
       CORE_RST_EN_REG for their clock & reset registers */
    switch(periph) {
    case PERIPH_SDMMC_MODULE:
    case PERIPH_SDIO_SLAVE_MODULE:
    case PERIPH_EMAC_MODULE:
    case PERIPH_RNG_MODULE:
    case PERIPH_WIFI_MODULE:
    case PERIPH_BT_MODULE:
    case PERIPH_WIFI_BT_COMMON_MODULE:
    case PERIPH_BT_BASEBAND_MODULE:
    case PERIPH_BT_LC_MODULE:
        return true;
    default:
        return false;
    }
}