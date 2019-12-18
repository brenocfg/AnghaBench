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
 int ZM_CMD_CONFIG ; 
 int /*<<< orphan*/  ZM_OID_INTERNAL_WRITE ; 
 int /*<<< orphan*/  zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfHpConfigFM(zdev_t* dev, u32_t RxMaxSize, u32_t DontRetransmit)
{
    u32_t cmd[3];
    u16_t ret;

    cmd[0] = 8 | (ZM_CMD_CONFIG << 8);
    cmd[1] = RxMaxSize;          /* zgRxMaxSize */
    cmd[2] = DontRetransmit;     /* zgDontRetransmit */

    ret = zfIssueCmd(dev, cmd, 12, ZM_OID_INTERNAL_WRITE, 0);
}