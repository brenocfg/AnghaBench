#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  proposed_mac; } ;
struct flexcop_device {TYPE_1__ dvb_adapter; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  err (char*) ; 
 int flexcop_eeprom_lrc_read (struct flexcop_device*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int flexcop_eeprom_check_mac_addr(struct flexcop_device *fc, int extended)
{
	u8 buf[8];
	int ret = 0;

	if ((ret = flexcop_eeprom_lrc_read(fc,0x3f8,buf,8,4)) == 0) {
		if (extended != 0) {
			err("TODO: extended (EUI64) MAC addresses aren't "
				"completely supported yet");
			ret = -EINVAL;
		} else
			memcpy(fc->dvb_adapter.proposed_mac,buf,6);
	}
	return ret;
}