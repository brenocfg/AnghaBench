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
 int ZM_OID_SYNTH ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int,int /*<<< orphan*/ ) ; 

u32_t zfiDbgSetIFSynthesizer(zdev_t* dev, u32_t value)
{
    u32_t cmd[2];
    u16_t ret;

	/* len[4] : type[0x32] : seq[?] */
    cmd[0] = 0x4 | (ZM_OID_SYNTH << 8);
    cmd[1] = value;

    ret = zfIssueCmd(dev, cmd, 8, ZM_OID_SYNTH, 0);
    return ret;
}