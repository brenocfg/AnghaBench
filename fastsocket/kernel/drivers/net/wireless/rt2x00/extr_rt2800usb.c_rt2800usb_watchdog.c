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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBF_CFG ; 
 int /*<<< orphan*/  TXRXQ_PCNT ; 
 int /*<<< orphan*/  TXRXQ_PCNT_TX0Q ; 
 int /*<<< orphan*/  TXRXQ_PCNT_TX1Q ; 
 scalar_t__ rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*) ; 
 int /*<<< orphan*/  rt2x00usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00usb_watchdog (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rt2800usb_watchdog(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u32 reg;

	rt2x00usb_register_read(rt2x00dev, TXRXQ_PCNT, &reg);
	if (rt2x00_get_field32(reg, TXRXQ_PCNT_TX0Q)) {
		rt2x00_warn(rt2x00dev, "TX HW queue 0 timed out, invoke forced kick\n");

		rt2x00usb_register_write(rt2x00dev, PBF_CFG, 0xf40012);

		for (i = 0; i < 10; i++) {
			udelay(10);
			if (!rt2x00_get_field32(reg, TXRXQ_PCNT_TX0Q))
				break;
		}

		rt2x00usb_register_write(rt2x00dev, PBF_CFG, 0xf40006);
	}

	rt2x00usb_register_read(rt2x00dev, TXRXQ_PCNT, &reg);
	if (rt2x00_get_field32(reg, TXRXQ_PCNT_TX1Q)) {
		rt2x00_warn(rt2x00dev, "TX HW queue 1 timed out, invoke forced kick\n");

		rt2x00usb_register_write(rt2x00dev, PBF_CFG, 0xf4000a);

		for (i = 0; i < 10; i++) {
			udelay(10);
			if (!rt2x00_get_field32(reg, TXRXQ_PCNT_TX1Q))
				break;
		}

		rt2x00usb_register_write(rt2x00dev, PBF_CFG, 0xf40006);
	}

	rt2x00usb_watchdog(rt2x00dev);
}