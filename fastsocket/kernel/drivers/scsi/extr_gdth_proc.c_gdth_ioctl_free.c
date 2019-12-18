#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong64 ;
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_3__ {char* pscratch; int /*<<< orphan*/  pdev; int /*<<< orphan*/  smp_lock; int /*<<< orphan*/  scratch_busy; } ;
typedef  TYPE_1__ gdth_ha_str ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gdth_ioctl_free(gdth_ha_str *ha, int size, char *buf, ulong64 paddr)
{
    ulong flags;

    if (buf == ha->pscratch) {
	spin_lock_irqsave(&ha->smp_lock, flags);
        ha->scratch_busy = FALSE;
	spin_unlock_irqrestore(&ha->smp_lock, flags);
    } else {
        pci_free_consistent(ha->pdev, size, buf, paddr);
    }
}