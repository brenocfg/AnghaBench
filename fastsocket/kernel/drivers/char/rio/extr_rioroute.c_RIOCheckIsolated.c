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
struct rio_info {int dummy; } ;
struct Host {int /*<<< orphan*/  HostLock; } ;

/* Variables and functions */
 scalar_t__ RIOCheck (struct Host*,unsigned int) ; 
 int /*<<< orphan*/  RIOIsolate (struct rio_info*,struct Host*,unsigned int) ; 
 int /*<<< orphan*/  RIOSetChange (struct rio_info*) ; 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  rio_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rio_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int RIOCheckIsolated(struct rio_info *p, struct Host *HostP, unsigned int UnitId)
{
	unsigned long flags;
	rio_spin_lock_irqsave(&HostP->HostLock, flags);

	if (RIOCheck(HostP, UnitId)) {
		rio_dprintk(RIO_DEBUG_ROUTE, "Unit %d is NOT isolated\n", UnitId);
		rio_spin_unlock_irqrestore(&HostP->HostLock, flags);
		return (0);
	}

	RIOIsolate(p, HostP, UnitId);
	RIOSetChange(p);
	rio_spin_unlock_irqrestore(&HostP->HostLock, flags);
	return 1;
}