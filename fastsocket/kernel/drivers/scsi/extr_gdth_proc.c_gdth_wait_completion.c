#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ unchar ;
typedef  int /*<<< orphan*/  ulong ;
struct gdth_cmndinfo {scalar_t__ wait_for_completion; } ;
struct TYPE_10__ {int /*<<< orphan*/  smp_lock; TYPE_1__* cmd_tab; } ;
typedef  TYPE_3__ gdth_ha_str ;
struct TYPE_11__ {TYPE_2__* device; } ;
struct TYPE_9__ {scalar_t__ channel; scalar_t__ id; } ;
struct TYPE_8__ {TYPE_4__* cmnd; } ;
typedef  TYPE_4__ Scsi_Cmnd ;

/* Variables and functions */
 int GDTH_MAXCMDS ; 
 int /*<<< orphan*/  SPECIAL_SCP (TYPE_4__*) ; 
 int /*<<< orphan*/  barrier () ; 
 struct gdth_cmndinfo* gdth_cmnd_priv (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gdth_wait_completion(gdth_ha_str *ha, int busnum, int id)
{
    ulong flags;
    int i;
    Scsi_Cmnd *scp;
    struct gdth_cmndinfo *cmndinfo;
    unchar b, t;

    spin_lock_irqsave(&ha->smp_lock, flags);

    for (i = 0; i < GDTH_MAXCMDS; ++i) {
        scp = ha->cmd_tab[i].cmnd;
        cmndinfo = gdth_cmnd_priv(scp);

        b = scp->device->channel;
        t = scp->device->id;
        if (!SPECIAL_SCP(scp) && t == (unchar)id && 
            b == (unchar)busnum) {
            cmndinfo->wait_for_completion = 0;
            spin_unlock_irqrestore(&ha->smp_lock, flags);
            while (!cmndinfo->wait_for_completion)
                barrier();
            spin_lock_irqsave(&ha->smp_lock, flags);
        }
    }
    spin_unlock_irqrestore(&ha->smp_lock, flags);
}