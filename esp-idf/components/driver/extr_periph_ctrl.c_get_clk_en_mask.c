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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int periph_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_BT_BASEBAND_EN ; 
 int /*<<< orphan*/  DPORT_BT_LC_EN ; 
 int /*<<< orphan*/  DPORT_CAN_CLK_EN ; 
 int /*<<< orphan*/  DPORT_I2C_EXT0_CLK_EN ; 
 int /*<<< orphan*/  DPORT_I2C_EXT1_CLK_EN ; 
 int /*<<< orphan*/  DPORT_I2S0_CLK_EN ; 
 int /*<<< orphan*/  DPORT_I2S1_CLK_EN ; 
 int /*<<< orphan*/  DPORT_LEDC_CLK_EN ; 
 int /*<<< orphan*/  DPORT_PCNT_CLK_EN ; 
 int /*<<< orphan*/  DPORT_PERI_EN_AES ; 
 int /*<<< orphan*/  DPORT_PERI_EN_RSA ; 
 int /*<<< orphan*/  DPORT_PERI_EN_SHA ; 
 int /*<<< orphan*/  DPORT_PWM0_CLK_EN ; 
 int /*<<< orphan*/  DPORT_PWM1_CLK_EN ; 
 int /*<<< orphan*/  DPORT_PWM2_CLK_EN ; 
 int /*<<< orphan*/  DPORT_PWM3_CLK_EN ; 
 int /*<<< orphan*/  DPORT_RMT_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI01_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI2_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI2_DMA_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI3_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI3_DMA_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI4_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI_DMA_CLK_EN ; 
 int /*<<< orphan*/  DPORT_SPI_SHARED_DMA_CLK_EN ; 
 int /*<<< orphan*/  DPORT_TIMERGROUP1_CLK_EN ; 
 int /*<<< orphan*/  DPORT_TIMERGROUP_CLK_EN ; 
 int /*<<< orphan*/  DPORT_UART1_CLK_EN ; 
 int /*<<< orphan*/  DPORT_UART2_CLK_EN ; 
 int /*<<< orphan*/  DPORT_UART_CLK_EN ; 
 int /*<<< orphan*/  DPORT_UHCI0_CLK_EN ; 
 int /*<<< orphan*/  DPORT_UHCI1_CLK_EN ; 
 int /*<<< orphan*/  DPORT_USB_CLK_EN ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_BT_EN_M ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_EMAC_EN ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_RNG_EN ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_SDIOSLAVE_EN ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_SDIO_HOST_EN ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_WIFI_BT_COMMON_M ; 
 int /*<<< orphan*/  DPORT_WIFI_CLK_WIFI_EN_M ; 
#define  PERIPH_AES_MODULE 167 
#define  PERIPH_BT_BASEBAND_MODULE 166 
#define  PERIPH_BT_LC_MODULE 165 
#define  PERIPH_BT_MODULE 164 
#define  PERIPH_CAN_MODULE 163 
#define  PERIPH_EMAC_MODULE 162 
#define  PERIPH_FSPI_MODULE 161 
#define  PERIPH_HSPI_MODULE 160 
#define  PERIPH_I2C0_MODULE 159 
#define  PERIPH_I2C1_MODULE 158 
#define  PERIPH_I2S0_MODULE 157 
#define  PERIPH_I2S1_MODULE 156 
#define  PERIPH_LEDC_MODULE 155 
#define  PERIPH_PCNT_MODULE 154 
#define  PERIPH_PWM0_MODULE 153 
#define  PERIPH_PWM1_MODULE 152 
#define  PERIPH_PWM2_MODULE 151 
#define  PERIPH_PWM3_MODULE 150 
#define  PERIPH_RMT_MODULE 149 
#define  PERIPH_RNG_MODULE 148 
#define  PERIPH_RSA_MODULE 147 
#define  PERIPH_SDIO_SLAVE_MODULE 146 
#define  PERIPH_SDMMC_MODULE 145 
#define  PERIPH_SHA_MODULE 144 
#define  PERIPH_SPI2_DMA_MODULE 143 
#define  PERIPH_SPI3_DMA_MODULE 142 
#define  PERIPH_SPI_DMA_MODULE 141 
#define  PERIPH_SPI_MODULE 140 
#define  PERIPH_SPI_SHARED_DMA_MODULE 139 
#define  PERIPH_TIMG0_MODULE 138 
#define  PERIPH_TIMG1_MODULE 137 
#define  PERIPH_UART0_MODULE 136 
#define  PERIPH_UART1_MODULE 135 
#define  PERIPH_UART2_MODULE 134 
#define  PERIPH_UHCI0_MODULE 133 
#define  PERIPH_UHCI1_MODULE 132 
#define  PERIPH_USB_MODULE 131 
#define  PERIPH_VSPI_MODULE 130 
#define  PERIPH_WIFI_BT_COMMON_MODULE 129 
#define  PERIPH_WIFI_MODULE 128 

__attribute__((used)) static uint32_t get_clk_en_mask(periph_module_t periph)
{
    switch(periph) {
        case PERIPH_RMT_MODULE:
            return DPORT_RMT_CLK_EN;
        case PERIPH_LEDC_MODULE:
            return DPORT_LEDC_CLK_EN;
        case PERIPH_UART0_MODULE:
            return DPORT_UART_CLK_EN;
        case PERIPH_UART1_MODULE:
            return DPORT_UART1_CLK_EN;
#if CONFIG_IDF_TARGET_ESP32
        case PERIPH_UART2_MODULE:
            return DPORT_UART2_CLK_EN;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        case PERIPH_USB_MODULE:
            return DPORT_USB_CLK_EN;
#endif
        case PERIPH_I2C0_MODULE:
            return DPORT_I2C_EXT0_CLK_EN;
        case PERIPH_I2C1_MODULE:
            return DPORT_I2C_EXT1_CLK_EN;
        case PERIPH_I2S0_MODULE:
            return DPORT_I2S0_CLK_EN;
        case PERIPH_I2S1_MODULE:
            return DPORT_I2S1_CLK_EN;
        case PERIPH_TIMG0_MODULE:
            return DPORT_TIMERGROUP_CLK_EN;
        case PERIPH_TIMG1_MODULE:
            return DPORT_TIMERGROUP1_CLK_EN;
        case PERIPH_PWM0_MODULE:
            return DPORT_PWM0_CLK_EN;
        case PERIPH_PWM1_MODULE:
            return DPORT_PWM1_CLK_EN;
        case PERIPH_PWM2_MODULE:
            return DPORT_PWM2_CLK_EN;
        case PERIPH_PWM3_MODULE:
            return DPORT_PWM3_CLK_EN;
        case PERIPH_UHCI0_MODULE:
            return DPORT_UHCI0_CLK_EN;
        case PERIPH_UHCI1_MODULE:
            return DPORT_UHCI1_CLK_EN;
        case PERIPH_PCNT_MODULE:
            return DPORT_PCNT_CLK_EN;
        case PERIPH_SPI_MODULE:
            return DPORT_SPI01_CLK_EN;
#if CONFIG_IDF_TARGET_ESP32
        case PERIPH_HSPI_MODULE:
            return DPORT_SPI2_CLK_EN;
        case PERIPH_VSPI_MODULE:
            return DPORT_SPI3_CLK_EN;
        case PERIPH_SPI_DMA_MODULE:
            return DPORT_SPI_DMA_CLK_EN;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        case PERIPH_FSPI_MODULE:
            return DPORT_SPI2_CLK_EN;
        case PERIPH_HSPI_MODULE:
            return DPORT_SPI3_CLK_EN;
        case PERIPH_VSPI_MODULE:
            return DPORT_SPI4_CLK_EN;
        case PERIPH_SPI2_DMA_MODULE:
            return DPORT_SPI2_DMA_CLK_EN;
        case PERIPH_SPI3_DMA_MODULE:
            return DPORT_SPI3_DMA_CLK_EN;
        case PERIPH_SPI_SHARED_DMA_MODULE:
            return DPORT_SPI_SHARED_DMA_CLK_EN;
#endif
        case PERIPH_SDMMC_MODULE:
            return DPORT_WIFI_CLK_SDIO_HOST_EN;
        case PERIPH_SDIO_SLAVE_MODULE:
            return DPORT_WIFI_CLK_SDIOSLAVE_EN;
        case PERIPH_CAN_MODULE:
            return DPORT_CAN_CLK_EN;
        case PERIPH_EMAC_MODULE:
            return DPORT_WIFI_CLK_EMAC_EN;
        case PERIPH_RNG_MODULE:
            return DPORT_WIFI_CLK_RNG_EN;
        case PERIPH_WIFI_MODULE:
#if CONFIG_IDF_TARGET_ESP32
            return DPORT_WIFI_CLK_WIFI_EN_M;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
            return 0;
#endif
        case PERIPH_BT_MODULE:
            return DPORT_WIFI_CLK_BT_EN_M;
        case PERIPH_WIFI_BT_COMMON_MODULE:
            return DPORT_WIFI_CLK_WIFI_BT_COMMON_M;
        case PERIPH_BT_BASEBAND_MODULE:
            return DPORT_BT_BASEBAND_EN;
        case PERIPH_BT_LC_MODULE:
            return DPORT_BT_LC_EN;
#if CONFIG_IDF_TARGET_ESP32
        case PERIPH_AES_MODULE:
            return DPORT_PERI_EN_AES;
        case PERIPH_SHA_MODULE:
            return DPORT_PERI_EN_SHA;
        case PERIPH_RSA_MODULE:
            return DPORT_PERI_EN_RSA;
#endif
        default:
            return 0;
    }
}