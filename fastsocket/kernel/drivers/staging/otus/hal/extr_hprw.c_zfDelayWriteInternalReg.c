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
typedef  void* u32_t ;
typedef  int u16_t ;
struct TYPE_3__ {size_t delayWcmdCount; void** delayWcmdVal; void** delayWcmdAddr; } ;
struct zsHpPriv {TYPE_1__ cmd; } ;
struct TYPE_4__ {struct zsHpPriv* hpPrivate; } ;

/* Variables and functions */
 int ZM_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  ZM_OID_INTERNAL_WRITE ; 
 TYPE_2__* wd ; 
 int zfIssueCmd (int /*<<< orphan*/ *,void**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfDelayWriteInternalReg(zdev_t* dev, u32_t addr, u32_t val)
{
    u32_t cmd[(ZM_MAX_CMD_SIZE/4)];
    u16_t i;
    u16_t ret;
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);
    hpPriv=wd->hpPrivate;

    zmw_declare_for_critical_section();

    /* enter critical section */
    zmw_enter_critical_section(dev);

    /* Store command to global buffer */
    hpPriv->cmd.delayWcmdAddr[hpPriv->cmd.delayWcmdCount] = addr;
    hpPriv->cmd.delayWcmdVal[hpPriv->cmd.delayWcmdCount++] = val;

    /* If pending command reach size limit */
    if ((hpPriv->cmd.delayWcmdCount) >= ((ZM_MAX_CMD_SIZE - 4) >> 3))
    {
        cmd[0] = 0x00000100 + (hpPriv->cmd.delayWcmdCount<<3);

        /* copy command to cmd buffer */
        for (i=0; i<hpPriv->cmd.delayWcmdCount; i++)
        {
            cmd[1+(i<<1)] = hpPriv->cmd.delayWcmdAddr[i];
            cmd[2+(i<<1)] = hpPriv->cmd.delayWcmdVal[i];
        }
        /* reset pending command */
        hpPriv->cmd.delayWcmdCount = 0;

        /* leave critical section */
        zmw_leave_critical_section(dev);

        /* issue write command */
        ret = zfIssueCmd(dev, cmd, 4+(i<<3), ZM_OID_INTERNAL_WRITE, NULL);

        return 1;
    }
    else
    {
        /* leave critical section */
        zmw_leave_critical_section(dev);

        return 0;
    }
}