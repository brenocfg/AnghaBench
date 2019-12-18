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
 int ZM_CMD_DKTX_STATUS ; 
 int /*<<< orphan*/  ZM_OID_DKTX_STATUS ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32_t zfiDbgQueryHwTxBusy(zdev_t* dev)
{
    u32_t cmd[1];
    u16_t ret;

	/* len[4] : type[0xC0] : seq[?] */
	cmd[0] = 0 | (ZM_CMD_DKTX_STATUS << 8);

    ret = zfIssueCmd(dev, cmd, 4, ZM_OID_DKTX_STATUS, 0);
    return ret;
}