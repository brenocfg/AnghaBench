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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 short BB_HOST_BANG_CLK ; 
 int BB_HOST_BANG_EN ; 
 int BB_HOST_BANG_RW ; 
 int /*<<< orphan*/  RFPinsEnable ; 
 int /*<<< orphan*/  RFPinsInput ; 
 int /*<<< orphan*/  RFPinsOutput ; 
 int /*<<< orphan*/  RFPinsSelect ; 
 int read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 read_rtl8225(struct net_device *dev, u8 adr)
{
	u32 data2Write = ((u32)(adr & 0x1f)) << 27;
	u32 dataRead;
	u32 mask;
	u16 oval,oval2,oval3,tmp;
	int i;
	short bit, rw;
	u8 wLength = 6;
	u8 rLength = 12;
	u8 low2high = 0;

	oval = read_nic_word(dev, RFPinsOutput);
	oval2 = read_nic_word(dev, RFPinsEnable);
	oval3 = read_nic_word(dev, RFPinsSelect);

	write_nic_word(dev, RFPinsEnable, (oval2|0xf));
	write_nic_word(dev, RFPinsSelect, (oval3|0xf));

	dataRead = 0;

	oval &= ~0xf;

	write_nic_word(dev, RFPinsOutput, oval | BB_HOST_BANG_EN ); udelay(4);

	write_nic_word(dev, RFPinsOutput, oval ); udelay(5);

	rw = 0;

	mask = (low2high) ? 0x01 : (((u32)0x01)<<(32-1));

	for (i = 0; i < wLength/2; i++) {
		bit = ((data2Write&mask) != 0) ? 1 : 0;
		write_nic_word(dev, RFPinsOutput, bit|oval | rw); udelay(1);

		write_nic_word(dev, RFPinsOutput, bit|oval | BB_HOST_BANG_CLK | rw); udelay(2);
		write_nic_word(dev, RFPinsOutput, bit|oval | BB_HOST_BANG_CLK | rw); udelay(2);

		mask = (low2high) ? (mask<<1): (mask>>1);

		if (i == 2) {
			rw = BB_HOST_BANG_RW;
			write_nic_word(dev, RFPinsOutput, bit|oval | BB_HOST_BANG_CLK | rw); udelay(2);
			write_nic_word(dev, RFPinsOutput, bit|oval | rw); udelay(2);
			break;
		}

		bit = ((data2Write&mask) != 0) ? 1: 0;

		write_nic_word(dev, RFPinsOutput, oval|bit|rw| BB_HOST_BANG_CLK); udelay(2);
		write_nic_word(dev, RFPinsOutput, oval|bit|rw| BB_HOST_BANG_CLK); udelay(2);

		write_nic_word(dev, RFPinsOutput, oval| bit |rw); udelay(1);

		mask = (low2high) ? (mask<<1) : (mask>>1);
	}

	write_nic_word(dev, RFPinsOutput, rw|oval); udelay(2);
	mask = (low2high) ? 0x01 : (((u32)0x01) << (12-1));

	/*
	 * We must set data pin to HW controled, otherwise RF can't driver it
	 * and value RF register won't be able to read back properly.
	 */
	write_nic_word(dev, RFPinsEnable, (oval2 & (~0x01)));

	for (i = 0; i < rLength; i++) {
		write_nic_word(dev, RFPinsOutput, rw|oval); udelay(1);

		write_nic_word(dev, RFPinsOutput, rw|oval|BB_HOST_BANG_CLK); udelay(2);
		write_nic_word(dev, RFPinsOutput, rw|oval|BB_HOST_BANG_CLK); udelay(2);
		write_nic_word(dev, RFPinsOutput, rw|oval|BB_HOST_BANG_CLK); udelay(2);
		tmp = read_nic_word(dev, RFPinsInput);

		dataRead |= (tmp & BB_HOST_BANG_CLK ? mask : 0);

		write_nic_word(dev, RFPinsOutput, (rw|oval)); udelay(2);

		mask = (low2high) ? (mask<<1) : (mask>>1);
	}

	write_nic_word(dev, RFPinsOutput, BB_HOST_BANG_EN|BB_HOST_BANG_RW|oval); udelay(2);

	write_nic_word(dev, RFPinsEnable, oval2);
	write_nic_word(dev, RFPinsSelect, oval3); /* Set To SW Switch */
	write_nic_word(dev, RFPinsOutput, 0x3a0);

	return dataRead;
}