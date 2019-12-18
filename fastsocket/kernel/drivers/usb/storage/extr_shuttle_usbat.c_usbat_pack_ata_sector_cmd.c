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

/* Variables and functions */

__attribute__((used)) static void usbat_pack_ata_sector_cmd(unsigned char *buf,
					unsigned char thistime,
					u32 sector, unsigned char cmd)
{
	buf[0] = 0;
	buf[1] = thistime;
	buf[2] = sector & 0xFF;
	buf[3] = (sector >>  8) & 0xFF;
	buf[4] = (sector >> 16) & 0xFF;
	buf[5] = 0xE0 | ((sector >> 24) & 0x0F);
	buf[6] = cmd;
}