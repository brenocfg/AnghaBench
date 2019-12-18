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
 int /*<<< orphan*/  AHB_20_22MHZ ; 
 int AR9170_GPIO_REG_PORT_DATA ; 
 int AR9170_GPIO_REG_PORT_TYPE ; 
 int AR9170_MAC_POWER_STATE_CTRL_RESET ; 
 int AR9170_MAC_REG_DMA_TRIGGER ; 
 int AR9170_MAC_REG_POWER_STATE_CTRL ; 
 int AR9170_PHY_ACTIVE_DIS ; 
 int AR9170_PHY_ADC_CTL_OFF_PWDADC ; 
 int AR9170_PHY_ADC_CTL_OFF_PWDDAC ; 
 int AR9170_PHY_ADC_SCTL_SEL_EXTERNAL_RADIO ; 
 int AR9170_PHY_ADC_SCTL_SEL_INTERNAL_ADDAC ; 
 int AR9170_PHY_REG_ACTIVE ; 
 int AR9170_PHY_REG_ADC_CTL ; 
 int AR9170_PHY_REG_ADC_SERIAL_CTL ; 
 int AR9170_PTA_DMA_MODE_CTRL_DISABLE_USB ; 
 int AR9170_PTA_DMA_MODE_CTRL_RESET ; 
 int /*<<< orphan*/  AR9170_PTA_REG_DMA_MODE_CTRL ; 
 int AR9170_PWR_REG_BASE ; 
 int AR9170_PWR_REG_PLL_ADDAC ; 
 int AR9170_PWR_REG_RESET ; 
 int AR9170_PWR_RESET_COMMIT_RESET_MASK ; 
 int AR9170_PWR_RESET_DMA_MASK ; 
 int AR9170_PWR_RESET_WLAN_MASK ; 
 int AR9170_USB_DMA_CTL_DOWN_STREAM ; 
 int AR9170_USB_DMA_CTL_ENABLE_FROM_DEVICE ; 
 int AR9170_USB_DMA_CTL_ENABLE_TO_DEVICE ; 
 int AR9170_USB_DMA_CTL_UP_PACKET_MODE ; 
 int /*<<< orphan*/  AR9170_USB_REG_DMA_CTL ; 
 int /*<<< orphan*/  andl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clock_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  orl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set (int,int) ; 

__attribute__((used)) static void turn_power_off(void)
{
	set(AR9170_PHY_REG_ACTIVE, AR9170_PHY_ACTIVE_DIS);
	set(AR9170_PHY_REG_ADC_CTL, 0xa0000000 |
	    AR9170_PHY_ADC_CTL_OFF_PWDADC | AR9170_PHY_ADC_CTL_OFF_PWDDAC);

	/* This will also turn-off the LEDs */
	set(AR9170_GPIO_REG_PORT_DATA, 0);
	set(AR9170_GPIO_REG_PORT_TYPE, 0xf);

	set(AR9170_PWR_REG_BASE, 0x40021);

	set(AR9170_MAC_REG_DMA_TRIGGER, 0);

	andl(AR9170_USB_REG_DMA_CTL, ~(AR9170_USB_DMA_CTL_ENABLE_TO_DEVICE |
				       AR9170_USB_DMA_CTL_ENABLE_FROM_DEVICE |
				       AR9170_USB_DMA_CTL_UP_PACKET_MODE |
				       AR9170_USB_DMA_CTL_DOWN_STREAM));

	/* Do a software reset to PTA component */
	orl(AR9170_PTA_REG_DMA_MODE_CTRL, AR9170_PTA_DMA_MODE_CTRL_RESET);
	andl(AR9170_PTA_REG_DMA_MODE_CTRL, ~AR9170_PTA_DMA_MODE_CTRL_RESET);

	orl(AR9170_PTA_REG_DMA_MODE_CTRL, AR9170_PTA_DMA_MODE_CTRL_DISABLE_USB);

	set(AR9170_MAC_REG_POWER_STATE_CTRL,
	    AR9170_MAC_POWER_STATE_CTRL_RESET);

	/* Reset USB FIFO */
	set(AR9170_PWR_REG_RESET, AR9170_PWR_RESET_COMMIT_RESET_MASK |
				  AR9170_PWR_RESET_DMA_MASK |
				  AR9170_PWR_RESET_WLAN_MASK);
	set(AR9170_PWR_REG_RESET, 0x0);

	clock_set(AHB_20_22MHZ, false);

	set(AR9170_PWR_REG_PLL_ADDAC, 0x5163);	/* 0x502b; */
	set(AR9170_PHY_REG_ADC_SERIAL_CTL, AR9170_PHY_ADC_SCTL_SEL_EXTERNAL_RADIO);
	set(0x1c589c, 0);	/* 7-0 */
	set(0x1c589c, 0);	/* 15-8 */
	set(0x1c589c, 0);	/* 23-16 */
	set(0x1c589c, 0);	/* 31- */
	set(0x1c589c, 0);	/* 39- */
	set(0x1c589c, 0);	/* 47- */
	set(0x1c589c, 0);	/* 55- */
	set(0x1c589c, 0xf8);	/* 63- */
	set(0x1c589c, 0x27);	/* 0x24;	71-	modified */
	set(0x1c589c, 0xf9);	/* 79- */
	set(0x1c589c, 0x90);	/* 87- */
	set(0x1c589c, 0x04);	/* 95- */
	set(0x1c589c, 0x48);	/* 103- */
	set(0x1c589c, 0x19);	/* 0;		111-	modified */
	set(0x1c589c, 0);	/* 119- */
	set(0x1c589c, 0);	/* 127- */
	set(0x1c589c, 0);	/* 135- */
	set(0x1c589c, 0);	/* 143- */
	set(0x1c589c, 0);	/* 151- */
	set(0x1c589c, 0x70);	/* 159- */
	set(0x1c589c, 0x0c);	/* 167- */
	set(0x1c589c, 0);	/* 175- */
	set(0x1c589c, 0);	/* 183-176 */
	set(0x1c589c, 0);	/* 191-184 */
	set(0x1c589c, 0);	/* 199- */
	set(0x1c589c, 0);	/* 207- */
	set(0x1c589c, 0);	/* 215- */
	set(0x1c589c, 0);	/* 223- */
	set(0x1c589c, 0);	/* 231- */
	set(0x1c58c4, 0);	/* 233- 232 */
	set(AR9170_PHY_REG_ADC_SERIAL_CTL, AR9170_PHY_ADC_SCTL_SEL_INTERNAL_ADDAC);
}