#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* device; } ;
struct TYPE_7__ {TYPE_1__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_3__ Scsi_Cmnd ;

/* Variables and functions */
 int __in2000_abort (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int in2000_abort(Scsi_Cmnd * cmd)
{
	int rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = __in2000_abort(cmd);
	spin_unlock_irq(cmd->device->host->host_lock);

	return rc;
}