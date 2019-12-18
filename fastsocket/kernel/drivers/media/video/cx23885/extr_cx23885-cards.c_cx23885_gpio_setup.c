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
struct cx23885_dev {int board; } ;

/* Variables and functions */
#define  CX23885_BOARD_COMPRO_VIDEOMATE_E650F 152 
#define  CX23885_BOARD_COMPRO_VIDEOMATE_E800 151 
#define  CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP 150 
#define  CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP 149 
#define  CX23885_BOARD_GOTVIEW_X5_3D_HYBRID 148 
#define  CX23885_BOARD_HAUPPAUGE_HVR1200 147 
#define  CX23885_BOARD_HAUPPAUGE_HVR1210 146 
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 145 
#define  CX23885_BOARD_HAUPPAUGE_HVR1255 144 
#define  CX23885_BOARD_HAUPPAUGE_HVR1270 143 
#define  CX23885_BOARD_HAUPPAUGE_HVR1275 142 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 141 
#define  CX23885_BOARD_HAUPPAUGE_HVR1400 140 
#define  CX23885_BOARD_HAUPPAUGE_HVR1500 139 
#define  CX23885_BOARD_HAUPPAUGE_HVR1500Q 138 
#define  CX23885_BOARD_HAUPPAUGE_HVR1700 137 
#define  CX23885_BOARD_HAUPPAUGE_HVR1800 136 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 135 
#define  CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H 134 
#define  CX23885_BOARD_LEADTEK_WINFAST_PXTV1200 133 
#define  CX23885_BOARD_MAGICPRO_PROHDTVE2 132 
#define  CX23885_BOARD_MYGICA_X8506 131 
#define  CX23885_BOARD_MYGICA_X8558PRO 130 
#define  CX23885_BOARD_NETUP_DUAL_DVBS2_CI 129 
#define  CX23885_BOARD_TBS_6920 128 
 int /*<<< orphan*/  GP0_IO ; 
 int GPIO_0 ; 
 int GPIO_1 ; 
 int GPIO_13 ; 
 int GPIO_14 ; 
 int GPIO_15 ; 
 int GPIO_2 ; 
 int GPIO_5 ; 
 int GPIO_6 ; 
 int GPIO_9 ; 
 int /*<<< orphan*/  GPIO_ISM ; 
 int /*<<< orphan*/  MC417_CTL ; 
 int /*<<< orphan*/  MC417_OEN ; 
 int /*<<< orphan*/  MC417_RWD ; 
 int /*<<< orphan*/  cx23885_gpio_clear (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  cx23885_gpio_enable (struct cx23885_dev*,int,int) ; 
 int /*<<< orphan*/  cx23885_gpio_set (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mc417_gpio_clear (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  mc417_gpio_enable (struct cx23885_dev*,int,int) ; 
 int /*<<< orphan*/  mc417_gpio_set (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

void cx23885_gpio_setup(struct cx23885_dev *dev)
{
	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
		/* GPIO-0 cx24227 demodulator reset */
		cx_set(GP0_IO, 0x00010001); /* Bring the part out of reset */
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1500:
		/* GPIO-0 cx24227 demodulator */
		/* GPIO-2 xc3028 tuner */

		/* Put the parts into reset */
		cx_set(GP0_IO, 0x00050000);
		cx_clear(GP0_IO, 0x00000005);
		msleep(5);

		/* Bring the parts out of reset */
		cx_set(GP0_IO, 0x00050005);
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1500Q:
		/* GPIO-0 cx24227 demodulator reset */
		/* GPIO-2 xc5000 tuner reset */
		cx_set(GP0_IO, 0x00050005); /* Bring the part out of reset */
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1800:
		/* GPIO-0 656_CLK */
		/* GPIO-1 656_D0 */
		/* GPIO-2 8295A Reset */
		/* GPIO-3-10 cx23417 data0-7 */
		/* GPIO-11-14 cx23417 addr0-3 */
		/* GPIO-15-18 cx23417 READY, CS, RD, WR */
		/* GPIO-19 IR_RX */

		/* CX23417 GPIO's */
		/* EIO15 Zilog Reset */
		/* EIO14 S5H1409/CX24227 Reset */
		mc417_gpio_enable(dev, GPIO_15 | GPIO_14, 1);

		/* Put the demod into reset and protect the eeprom */
		mc417_gpio_clear(dev, GPIO_15 | GPIO_14);
		mdelay(100);

		/* Bring the demod and blaster out of reset */
		mc417_gpio_set(dev, GPIO_15 | GPIO_14);
		mdelay(100);

		/* Force the TDA8295A into reset and back */
		cx23885_gpio_enable(dev, GPIO_2, 1);
		cx23885_gpio_set(dev, GPIO_2);
		mdelay(20);
		cx23885_gpio_clear(dev, GPIO_2);
		mdelay(20);
		cx23885_gpio_set(dev, GPIO_2);
		mdelay(20);
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1200:
		/* GPIO-0 tda10048 demodulator reset */
		/* GPIO-2 tda18271 tuner reset */

		/* Put the parts into reset and back */
		cx_set(GP0_IO, 0x00050000);
		mdelay(20);
		cx_clear(GP0_IO, 0x00000005);
		mdelay(20);
		cx_set(GP0_IO, 0x00050005);
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1700:
		/* GPIO-0 TDA10048 demodulator reset */
		/* GPIO-2 TDA8295A Reset */
		/* GPIO-3-10 cx23417 data0-7 */
		/* GPIO-11-14 cx23417 addr0-3 */
		/* GPIO-15-18 cx23417 READY, CS, RD, WR */

		/* The following GPIO's are on the interna AVCore (cx25840) */
		/* GPIO-19 IR_RX */
		/* GPIO-20 IR_TX 416/DVBT Select */
		/* GPIO-21 IIS DAT */
		/* GPIO-22 IIS WCLK */
		/* GPIO-23 IIS BCLK */

		/* Put the parts into reset and back */
		cx_set(GP0_IO, 0x00050000);
		mdelay(20);
		cx_clear(GP0_IO, 0x00000005);
		mdelay(20);
		cx_set(GP0_IO, 0x00050005);
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1400:
		/* GPIO-0  Dibcom7000p demodulator reset */
		/* GPIO-2  xc3028L tuner reset */
		/* GPIO-13 LED */

		/* Put the parts into reset and back */
		cx_set(GP0_IO, 0x00050000);
		mdelay(20);
		cx_clear(GP0_IO, 0x00000005);
		mdelay(20);
		cx_set(GP0_IO, 0x00050005);
		break;
	case CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP:
		/* GPIO-0 xc5000 tuner reset i2c bus 0 */
		/* GPIO-1 s5h1409 demod reset i2c bus 0 */
		/* GPIO-2 xc5000 tuner reset i2c bus 1 */
		/* GPIO-3 s5h1409 demod reset i2c bus 0 */

		/* Put the parts into reset and back */
		cx_set(GP0_IO, 0x000f0000);
		mdelay(20);
		cx_clear(GP0_IO, 0x0000000f);
		mdelay(20);
		cx_set(GP0_IO, 0x000f000f);
		break;
	case CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP:
		/* GPIO-0 portb xc3028 reset */
		/* GPIO-1 portb zl10353 reset */
		/* GPIO-2 portc xc3028 reset */
		/* GPIO-3 portc zl10353 reset */

		/* Put the parts into reset and back */
		cx_set(GP0_IO, 0x000f0000);
		mdelay(20);
		cx_clear(GP0_IO, 0x0000000f);
		mdelay(20);
		cx_set(GP0_IO, 0x000f000f);
		break;
	case CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	case CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	case CX23885_BOARD_COMPRO_VIDEOMATE_E800:
	case CX23885_BOARD_LEADTEK_WINFAST_PXTV1200:
		/* GPIO-2  xc3028 tuner reset */

		/* The following GPIO's are on the internal AVCore (cx25840) */
		/* GPIO-?  zl10353 demod reset */

		/* Put the parts into reset and back */
		cx_set(GP0_IO, 0x00040000);
		mdelay(20);
		cx_clear(GP0_IO, 0x00000004);
		mdelay(20);
		cx_set(GP0_IO, 0x00040004);
		break;
	case CX23885_BOARD_TBS_6920:
		cx_write(MC417_CTL, 0x00000036);
		cx_write(MC417_OEN, 0x00001000);
		cx_set(MC417_RWD, 0x00000002);
		mdelay(200);
		cx_clear(MC417_RWD, 0x00000800);
		mdelay(200);
		cx_set(MC417_RWD, 0x00000800);
		mdelay(200);
		break;
	case CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		/* GPIO-0 INTA from CiMax1
		   GPIO-1 INTB from CiMax2
		   GPIO-2 reset chips
		   GPIO-3 to GPIO-10 data/addr for CA
		   GPIO-11 ~CS0 to CiMax1
		   GPIO-12 ~CS1 to CiMax2
		   GPIO-13 ADL0 load LSB addr
		   GPIO-14 ADL1 load MSB addr
		   GPIO-15 ~RDY from CiMax
		   GPIO-17 ~RD to CiMax
		   GPIO-18 ~WR to CiMax
		 */
		cx_set(GP0_IO, 0x00040000); /* GPIO as out */
		/* GPIO1 and GPIO2 as INTA and INTB from CiMaxes, reset low */
		cx_clear(GP0_IO, 0x00030004);
		mdelay(100);/* reset delay */
		cx_set(GP0_IO, 0x00040004); /* GPIO as out, reset high */
		cx_write(MC417_CTL, 0x00000037);/* enable GPIO3-18 pins */
		/* GPIO-15 IN as ~ACK, rest as OUT */
		cx_write(MC417_OEN, 0x00001000);
		/* ~RD, ~WR high; ADL0, ADL1 low; ~CS0, ~CS1 high */
		cx_write(MC417_RWD, 0x0000c300);
		/* enable irq */
		cx_write(GPIO_ISM, 0x00000000);/* INTERRUPTS active low*/
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1270:
	case CX23885_BOARD_HAUPPAUGE_HVR1275:
	case CX23885_BOARD_HAUPPAUGE_HVR1255:
	case CX23885_BOARD_HAUPPAUGE_HVR1210:
		/* GPIO-5 RF Control: 0 = RF1 Terrestrial, 1 = RF2 Cable */
		/* GPIO-6 I2C Gate which can isolate the demod from the bus */
		/* GPIO-9 Demod reset */

		/* Put the parts into reset and back */
		cx23885_gpio_enable(dev, GPIO_9 | GPIO_6 | GPIO_5, 1);
		cx23885_gpio_set(dev, GPIO_9 | GPIO_6 | GPIO_5);
		cx23885_gpio_clear(dev, GPIO_9);
		mdelay(20);
		cx23885_gpio_set(dev, GPIO_9);
		break;
	case CX23885_BOARD_MYGICA_X8506:
	case CX23885_BOARD_MAGICPRO_PROHDTVE2:
		/* GPIO-0 (0)Analog / (1)Digital TV */
		/* GPIO-1 reset XC5000 */
		/* GPIO-2 reset LGS8GL5 / LGS8G75 */
		cx23885_gpio_enable(dev, GPIO_0 | GPIO_1 | GPIO_2, 1);
		cx23885_gpio_clear(dev, GPIO_1 | GPIO_2);
		mdelay(100);
		cx23885_gpio_set(dev, GPIO_0 | GPIO_1 | GPIO_2);
		mdelay(100);
		break;
	case CX23885_BOARD_MYGICA_X8558PRO:
		/* GPIO-0 reset first ATBM8830 */
		/* GPIO-1 reset second ATBM8830 */
		cx23885_gpio_enable(dev, GPIO_0 | GPIO_1, 1);
		cx23885_gpio_clear(dev, GPIO_0 | GPIO_1);
		mdelay(100);
		cx23885_gpio_set(dev, GPIO_0 | GPIO_1);
		mdelay(100);
		break;
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
		/* GPIO-0 656_CLK */
		/* GPIO-1 656_D0 */
		/* GPIO-2 Wake# */
		/* GPIO-3-10 cx23417 data0-7 */
		/* GPIO-11-14 cx23417 addr0-3 */
		/* GPIO-15-18 cx23417 READY, CS, RD, WR */
		/* GPIO-19 IR_RX */
		/* GPIO-20 C_IR_TX */
		/* GPIO-21 I2S DAT */
		/* GPIO-22 I2S WCLK */
		/* GPIO-23 I2S BCLK */
		/* ALT GPIO: EXP GPIO LATCH */

		/* CX23417 GPIO's */
		/* GPIO-14 S5H1411/CX24228 Reset */
		/* GPIO-13 EEPROM write protect */
		mc417_gpio_enable(dev, GPIO_14 | GPIO_13, 1);

		/* Put the demod into reset and protect the eeprom */
		mc417_gpio_clear(dev, GPIO_14 | GPIO_13);
		mdelay(100);

		/* Bring the demod out of reset */
		mc417_gpio_set(dev, GPIO_14);
		mdelay(100);

		/* CX24228 GPIO */
		/* Connected to IF / Mux */
		break;
	case CX23885_BOARD_GOTVIEW_X5_3D_HYBRID:
		cx_set(GP0_IO, 0x00010001); /* Bring the part out of reset */
		break;
	}
}