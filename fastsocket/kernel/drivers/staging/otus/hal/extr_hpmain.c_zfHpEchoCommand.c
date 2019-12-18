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
 int /*<<< orphan*/  ZM_CMD_ECHO ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u32_t zfHpEchoCommand(zdev_t* dev, u32_t value)
{
    u32_t cmd[2];
    u16_t ret;

    cmd[0] = 0x00008004;
    cmd[1] = value;

    ret = zfIssueCmd(dev, cmd, 8, ZM_CMD_ECHO, NULL);
    return ret;
}