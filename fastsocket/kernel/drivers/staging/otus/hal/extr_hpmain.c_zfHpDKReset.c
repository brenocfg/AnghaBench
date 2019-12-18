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
typedef  int u8_t ;
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int ZM_CMD_DKRESET ; 
 int ZM_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  ZM_OID_INTERNAL_WRITE ; 
 int /*<<< orphan*/  zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u16_t zfHpDKReset(zdev_t* dev, u8_t flag)
{
    u32_t cmd[(ZM_MAX_CMD_SIZE/4)];
    u16_t ret = 0;

    //zm_debug_msg0("CWY - Reset Tx and Rx");

    cmd[0] =  4 | (ZM_CMD_DKRESET << 8);
    cmd[1] = flag;

    ret = zfIssueCmd(dev, cmd, 8, ZM_OID_INTERNAL_WRITE, NULL);
    return ret;
}