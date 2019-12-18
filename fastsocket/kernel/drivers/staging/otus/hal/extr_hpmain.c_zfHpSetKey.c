#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u64_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct zsHpPriv {int camRollCallTable; } ;
struct TYPE_3__ {int /*<<< orphan*/  flagKeyChanging; } ;
struct TYPE_4__ {TYPE_1__ sta; struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_CMD_SET_KEY ; 
 int ZM_MAX_CMD_SIZE ; 
 TYPE_2__* wd ; 
 int zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u32_t zfHpSetKey(zdev_t* dev, u8_t user, u8_t keyId, u8_t type,
        u16_t* mac, u32_t* key)
{
    u32_t cmd[(ZM_MAX_CMD_SIZE/4)];
    u16_t ret;
    u16_t i;
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

#if 0   /* remove to zfCoreSetKey() */
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    wd->sta.flagKeyChanging++;
    zm_debug_msg1("   zfHpSetKey++++ ", wd->sta.flagKeyChanging);
    zmw_leave_critical_section(dev);
#endif

    cmd[0] = 0x0000281C;
    cmd[1] = ((u32_t)keyId<<16) + (u32_t)user;
    cmd[2] = ((u32_t)mac[0]<<16) + (u32_t)type;
    cmd[3] = ((u32_t)mac[2]<<16) + ((u32_t)mac[1]);

    for (i=0; i<4; i++)
    {
        cmd[4+i] = key[i];
    }

    if (user < 64)
    {
        hpPriv->camRollCallTable |= ((u64_t) 1) << user;
    }

    //ret = zfIssueCmd(dev, cmd, 32, ZM_OID_INTERNAL_WRITE, NULL);
    ret = zfIssueCmd(dev, cmd, 32, ZM_CMD_SET_KEY, NULL);
    return ret;
}