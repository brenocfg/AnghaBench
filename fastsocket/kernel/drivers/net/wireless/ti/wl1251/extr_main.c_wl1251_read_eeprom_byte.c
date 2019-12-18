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
struct wl1251 {int dummy; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EE_ADDR ; 
 int /*<<< orphan*/  EE_CTL ; 
 int EE_CTL_READ ; 
 int /*<<< orphan*/  EE_DATA ; 
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wl1251_read_eeprom_byte(struct wl1251 *wl, off_t offset, u8 *data)
{
	unsigned long timeout;

	wl1251_reg_write32(wl, EE_ADDR, offset);
	wl1251_reg_write32(wl, EE_CTL, EE_CTL_READ);

	/* EE_CTL_READ clears when data is ready */
	timeout = jiffies + msecs_to_jiffies(100);
	while (1) {
		if (!(wl1251_reg_read32(wl, EE_CTL) & EE_CTL_READ))
			break;

		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;

		msleep(1);
	}

	*data = wl1251_reg_read32(wl, EE_DATA);
	return 0;
}