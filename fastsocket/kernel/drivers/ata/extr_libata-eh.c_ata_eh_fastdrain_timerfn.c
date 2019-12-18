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
struct ata_queued_cmd {int /*<<< orphan*/  err_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  expires; } ;
struct ata_port {int fastdrain_cnt; int /*<<< orphan*/  lock; TYPE_1__ fastdrain_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ATA_EH_FASTDRAIN_INTERVAL ; 
 int ATA_MAX_QUEUE ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ata_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ata_eh_nr_in_flight (struct ata_port*) ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,unsigned int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void ata_eh_fastdrain_timerfn(unsigned long arg)
{
	struct ata_port *ap = (void *)arg;
	unsigned long flags;
	int cnt;

	spin_lock_irqsave(ap->lock, flags);

	cnt = ata_eh_nr_in_flight(ap);

	/* are we done? */
	if (!cnt)
		goto out_unlock;

	if (cnt == ap->fastdrain_cnt) {
		unsigned int tag;

		/* No progress during the last interval, tag all
		 * in-flight qcs as timed out and freeze the port.
		 */
		for (tag = 0; tag < ATA_MAX_QUEUE - 1; tag++) {
			struct ata_queued_cmd *qc = ata_qc_from_tag(ap, tag);
			if (qc)
				qc->err_mask |= AC_ERR_TIMEOUT;
		}

		ata_port_freeze(ap);
	} else {
		/* some qcs have finished, give it another chance */
		ap->fastdrain_cnt = cnt;
		ap->fastdrain_timer.expires =
			ata_deadline(jiffies, ATA_EH_FASTDRAIN_INTERVAL);
		add_timer(&ap->fastdrain_timer);
	}

 out_unlock:
	spin_unlock_irqrestore(ap->lock, flags);
}