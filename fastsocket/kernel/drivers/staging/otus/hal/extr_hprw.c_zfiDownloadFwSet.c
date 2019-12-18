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

/* Variables and functions */
 int ZM_CMD_FW_DL_INIT ; 
 int ZM_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  ZM_OID_FW_DL_INIT ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u32_t zfiDownloadFwSet(zdev_t *dev)
{
//softwarereset
//close watch dog
    u32_t cmd[(ZM_MAX_CMD_SIZE/4)];
    u32_t ret;

    cmd[0] = 0x00000008 | (ZM_CMD_FW_DL_INIT << 8);

    ret = zfIssueCmd(dev, cmd, 12, ZM_OID_FW_DL_INIT, NULL);

    return ret;
}