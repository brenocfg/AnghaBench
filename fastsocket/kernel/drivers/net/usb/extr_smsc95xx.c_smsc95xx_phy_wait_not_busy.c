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
typedef  int u32 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  MII_ADDR ; 
 int MII_BUSY_ ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  smsc95xx_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int smsc95xx_phy_wait_not_busy(struct usbnet *dev)
{
	unsigned long start_time = jiffies;
	u32 val;

	do {
		smsc95xx_read_reg(dev, MII_ADDR, &val);
		if (!(val & MII_BUSY_))
			return 0;
	} while (!time_after(jiffies, start_time + HZ));

	return -EIO;
}