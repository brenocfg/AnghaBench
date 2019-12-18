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
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int ZM_CMD_FLASH_ERASE ; 
 int ZM_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  ZM_OID_INTERNAL_WRITE ; 
 int /*<<< orphan*/  zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u16_t zfiDbgChipEraseFlash(zdev_t *dev)
{
    u32_t cmd[(ZM_MAX_CMD_SIZE/4)];
    u16_t ret;

    cmd[0] = 0x00000000 | (ZM_CMD_FLASH_ERASE << 8);

    ret = zfIssueCmd(dev, cmd, 4, ZM_OID_INTERNAL_WRITE, NULL);
    return ret;
}