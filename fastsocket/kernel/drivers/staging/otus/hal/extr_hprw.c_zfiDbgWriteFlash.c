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
 int ZM_CMD_WFLASH ; 
 int /*<<< orphan*/  ZM_OID_WRITE ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32_t zfiDbgWriteFlash(zdev_t* dev, u32_t addr, u32_t val)
{
    u32_t cmd[3];
    u16_t ret;

    //cmd[0] = 0x0000B008;
	/* len[0] : type[0xB0] : seq[?] */
    cmd[0] = 8 | (ZM_CMD_WFLASH << 8);
    cmd[1] = addr;
    cmd[2] = val;

    ret = zfIssueCmd(dev, cmd, 12, ZM_OID_WRITE, 0);
    return ret;
}