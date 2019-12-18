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
typedef  size_t u8 ;
struct TYPE_2__ {scalar_t__ refcnt; int /*<<< orphan*/  flags; int /*<<< orphan*/ * event_handler; int /*<<< orphan*/ * msg_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLER_DELETING ; 
 int HZ ; 
 size_t SCSI_NL_MAX_TRANSPORTS ; 
 int STATE_EHANDLER_BSY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  scsi_nl_lock ; 
 int scsi_nl_state ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* transports ; 

void
scsi_nl_remove_transport(u8 tport)
{
	unsigned long flags;

	spin_lock_irqsave(&scsi_nl_lock, flags);
	if (scsi_nl_state & STATE_EHANDLER_BSY) {
		spin_unlock_irqrestore(&scsi_nl_lock, flags);
		msleep(1);
		spin_lock_irqsave(&scsi_nl_lock, flags);
	}

	if (tport < SCSI_NL_MAX_TRANSPORTS) {
		transports[tport].flags |= HANDLER_DELETING;

		while (transports[tport].refcnt != 0) {
			spin_unlock_irqrestore(&scsi_nl_lock, flags);
			schedule_timeout_uninterruptible(HZ/4);
			spin_lock_irqsave(&scsi_nl_lock, flags);
		}
		transports[tport].msg_handler = NULL;
		transports[tport].event_handler = NULL;
		transports[tport].flags = 0;
	}

	spin_unlock_irqrestore(&scsi_nl_lock, flags);

	return;
}