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
typedef  int periph_module_t ;

/* Variables and functions */
 int DPORT_CAN_RST ; 
 int DPORT_EMAC_RST ; 
 int DPORT_I2C_EXT0_RST ; 
 int DPORT_I2C_EXT1_RST ; 
 int DPORT_I2S0_RST ; 
 int DPORT_I2S1_RST ; 
 int DPORT_LEDC_RST ; 
 int DPORT_PCNT_RST ; 
 int DPORT_PERI_EN_AES ; 
 int DPORT_PERI_EN_DIGITAL_SIGNATURE ; 
 int DPORT_PERI_EN_RSA ; 
 int DPORT_PERI_EN_SECUREBOOT ; 
 int DPORT_PERI_EN_SHA ; 
 int DPORT_PWM0_RST ; 
 int DPORT_PWM1_RST ; 
 int DPORT_PWM2_RST ; 
 int DPORT_PWM3_RST ; 
 int DPORT_RMT_RST ; 
 int DPORT_SDIO_HOST_RST ; 
 int DPORT_SDIO_RST ; 
 int DPORT_SPI01_RST ; 
 int DPORT_SPI2_DMA_RST ; 
 int DPORT_SPI2_RST ; 
 int DPORT_SPI3_DMA_RST ; 
 int DPORT_SPI3_RST ; 
 int DPORT_SPI4_RST ; 
 int DPORT_SPI_DMA_RST ; 
 int DPORT_SPI_SHARED_DMA_RST ; 
 int DPORT_TIMERGROUP1_RST ; 
 int DPORT_TIMERGROUP_RST ; 
 int DPORT_UART1_RST ; 
 int DPORT_UART2_RST ; 
 int DPORT_UART_RST ; 
 int DPORT_UHCI0_RST ; 
 int DPORT_UHCI1_RST ; 
 int DPORT_USB_RST ; 
#define  PERIPH_AES_MODULE 166 
#define  PERIPH_BT_BASEBAND_MODULE 165 
#define  PERIPH_BT_LC_MODULE 164 
#define  PERIPH_BT_MODULE 163 
#define  PERIPH_CAN_MODULE 162 
#define  PERIPH_EMAC_MODULE 161 
#define  PERIPH_FSPI_MODULE 160 
#define  PERIPH_HSPI_MODULE 159 
#define  PERIPH_I2C0_MODULE 158 
#define  PERIPH_I2C1_MODULE 157 
#define  PERIPH_I2S0_MODULE 156 
#define  PERIPH_I2S1_MODULE 155 
#define  PERIPH_LEDC_MODULE 154 
#define  PERIPH_PCNT_MODULE 153 
#define  PERIPH_PWM0_MODULE 152 
#define  PERIPH_PWM1_MODULE 151 
#define  PERIPH_PWM2_MODULE 150 
#define  PERIPH_PWM3_MODULE 149 
#define  PERIPH_RMT_MODULE 148 
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

__attribute__((used)) static uint32_t get_rst_en_mask(periph_module_t periph, bool enable)
{
    switch(periph) {
        case PERIPH_RMT_MODULE:
            return DPORT_RMT_RST;
        case PERIPH_LEDC_MODULE:
            return DPORT_LEDC_RST;
        case PERIPH_UART0_MODULE:
            return DPORT_UART_RST;
        case PERIPH_UART1_MODULE:
            return DPORT_UART1_RST;
#if CONFIG_IDF_TARGET_ESP32
        case PERIPH_UART2_MODULE:
            return DPORT_UART2_RST;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        case PERIPH_USB_MODULE:
            return DPORT_USB_RST;
#endif
        case PERIPH_I2C0_MODULE:
            return DPORT_I2C_EXT0_RST;
        case PERIPH_I2C1_MODULE:
            return DPORT_I2C_EXT1_RST;
        case PERIPH_I2S0_MODULE:
            return DPORT_I2S0_RST;
        case PERIPH_I2S1_MODULE:
            return DPORT_I2S1_RST;
        case PERIPH_TIMG0_MODULE:
            return DPORT_TIMERGROUP_RST;
        case PERIPH_TIMG1_MODULE:
            return DPORT_TIMERGROUP1_RST;
        case PERIPH_PWM0_MODULE:
            return DPORT_PWM0_RST;
        case PERIPH_PWM1_MODULE:
            return DPORT_PWM1_RST;
        case PERIPH_PWM2_MODULE:
            return DPORT_PWM2_RST;
        case PERIPH_PWM3_MODULE:
            return DPORT_PWM3_RST;
        case PERIPH_UHCI0_MODULE:
            return DPORT_UHCI0_RST;
        case PERIPH_UHCI1_MODULE:
            return DPORT_UHCI1_RST;
        case PERIPH_PCNT_MODULE:
            return DPORT_PCNT_RST;
        case PERIPH_SPI_MODULE:
            return DPORT_SPI01_RST;
#if CONFIG_IDF_TARGET_ESP32
        case PERIPH_HSPI_MODULE:
            return DPORT_SPI2_RST;
        case PERIPH_VSPI_MODULE:
            return DPORT_SPI3_RST;
        case PERIPH_SPI_DMA_MODULE:
            return DPORT_SPI_DMA_RST;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        case PERIPH_FSPI_MODULE:
            return DPORT_SPI2_RST;
        case PERIPH_HSPI_MODULE:
            return DPORT_SPI3_RST;
        case PERIPH_VSPI_MODULE:
            return DPORT_SPI4_RST;
        case PERIPH_SPI2_DMA_MODULE:
            return DPORT_SPI2_DMA_RST;
        case PERIPH_SPI3_DMA_MODULE:
            return DPORT_SPI3_DMA_RST;
        case PERIPH_SPI_SHARED_DMA_MODULE:
            return DPORT_SPI_SHARED_DMA_RST;
#endif
        case PERIPH_SDMMC_MODULE:
            return DPORT_SDIO_HOST_RST;
        case PERIPH_SDIO_SLAVE_MODULE:
            return DPORT_SDIO_RST;
        case PERIPH_CAN_MODULE:
            return DPORT_CAN_RST;
        case PERIPH_EMAC_MODULE:
            return DPORT_EMAC_RST;
#if CONFIG_IDF_TARGET_ESP32
        case PERIPH_AES_MODULE:
            if (enable == true) {
                // Clear reset on digital signature & secure boot units, otherwise AES unit is held in reset also.
                return (DPORT_PERI_EN_AES | DPORT_PERI_EN_DIGITAL_SIGNATURE | DPORT_PERI_EN_SECUREBOOT);
            } else {
                //Don't return other units to reset, as this pulls reset on RSA & SHA units, respectively.
                return DPORT_PERI_EN_AES;
            }
        case PERIPH_SHA_MODULE:
            if (enable == true) {
                // Clear reset on secure boot, otherwise SHA is held in reset
                return (DPORT_PERI_EN_SHA | DPORT_PERI_EN_SECUREBOOT);
            } else {
                // Don't assert reset on secure boot, otherwise AES is held in reset
                return DPORT_PERI_EN_SHA;
            }
        case PERIPH_RSA_MODULE:
            if (enable == true) {
                // Also clear reset on digital signature, otherwise RSA is held in reset
                return (DPORT_PERI_EN_RSA | DPORT_PERI_EN_DIGITAL_SIGNATURE);
            } else {
                // Don't reset digital signature unit, as this resets AES also
                return DPORT_PERI_EN_RSA;
            }
#endif
        case PERIPH_WIFI_MODULE:
        case PERIPH_BT_MODULE:
        case PERIPH_WIFI_BT_COMMON_MODULE:
        case PERIPH_BT_BASEBAND_MODULE:
        case PERIPH_BT_LC_MODULE:
            return 0;
        default:
            return 0;
    }
}