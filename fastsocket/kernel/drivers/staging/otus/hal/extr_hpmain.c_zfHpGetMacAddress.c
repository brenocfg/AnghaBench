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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_READ ; 
 int ZM_SEEPROM_HARDWARE_TYPE_OFFSET ; 
 int ZM_SEEPROM_HW_HEAVY_CLIP ; 
 int ZM_SEEPROM_MAC_ADDRESS_OFFSET ; 
 int ZM_SEEPROM_REGDOMAIN_OFFSET ; 
 int ZM_SEEPROM_VERISON_OFFSET ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32_t zfHpGetMacAddress(zdev_t* dev)
{
    u32_t cmd[7];
    u16_t ret;

    cmd[0] = 0x00000000 | 24;
    cmd[1] = ZM_SEEPROM_MAC_ADDRESS_OFFSET;
    cmd[2] = ZM_SEEPROM_MAC_ADDRESS_OFFSET+4;
    cmd[3] = ZM_SEEPROM_REGDOMAIN_OFFSET;
    cmd[4] = ZM_SEEPROM_VERISON_OFFSET;
    cmd[5] = ZM_SEEPROM_HARDWARE_TYPE_OFFSET;
    cmd[6] = ZM_SEEPROM_HW_HEAVY_CLIP;

    ret = zfIssueCmd(dev, cmd, 28, ZM_MAC_READ, 0);
    return ret;
}