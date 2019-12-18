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
 int /*<<< orphan*/  ZM_ANI_READ ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32_t zfHpAniUpdate(zdev_t* dev)
{
    u32_t cmd[5];
    u16_t ret;

    cmd[0] = 0x00000010;
    cmd[1] = 0x1c36e8;
    cmd[2] = 0x1c36ec;
    cmd[3] = 0x1c3cb4;
    cmd[4] = 0x1c3cb8;

    ret = zfIssueCmd(dev, cmd, 20, ZM_ANI_READ, 0);
    return ret;
}