#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct zsHpPriv {scalar_t__ halReInit; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int ZM_CMD_TALLY ; 
 int ZM_CMD_TALLY_APD ; 
 int /*<<< orphan*/  ZM_OID_TALLY ; 
 int /*<<< orphan*/  ZM_OID_TALLY_APD ; 
 TYPE_1__* wd ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfiDbgReadTally(zdev_t* dev)
{
    u32_t cmd[1];
    u16_t ret;
	zmw_get_wlan_dev(dev);

	if ( ((struct zsHpPriv*)wd->hpPrivate)->halReInit )
	{
	    return 1;
	}

	/* len[0] : type[0x81] : seq[?] */
    cmd[0] = 0 | (ZM_CMD_TALLY << 8);
    ret = zfIssueCmd(dev, cmd, 4, ZM_OID_TALLY, 0);

	/* len[0] : type[0x82] : seq[?] */
    cmd[0] = 0 | (ZM_CMD_TALLY_APD << 8);
    ret = zfIssueCmd(dev, cmd, 4, ZM_OID_TALLY_APD, 0);

    return ret;
}