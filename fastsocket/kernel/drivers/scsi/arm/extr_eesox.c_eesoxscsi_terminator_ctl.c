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
struct eesoxscsi_info {int /*<<< orphan*/  ctl_port; int /*<<< orphan*/  control; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  EESOX_TERM_ENABLE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eesoxscsi_terminator_ctl(struct Scsi_Host *host, int on_off)
{
	struct eesoxscsi_info *info = (struct eesoxscsi_info *)host->hostdata;
	unsigned long flags;

	spin_lock_irqsave(host->host_lock, flags);
	if (on_off)
		info->control |= EESOX_TERM_ENABLE;
	else
		info->control &= ~EESOX_TERM_ENABLE;

	writeb(info->control, info->ctl_port);
	spin_unlock_irqrestore(host->host_lock, flags);
}