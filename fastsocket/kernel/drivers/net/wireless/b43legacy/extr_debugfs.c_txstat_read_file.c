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
struct b43legacy_wldev {TYPE_1__* dfsentry; } ;
struct b43legacy_txstatus_log {int end; int /*<<< orphan*/  lock; struct b43legacy_txstatus* log; } ;
struct b43legacy_txstatus {int /*<<< orphan*/  acked; int /*<<< orphan*/  for_ampdu; int /*<<< orphan*/  intermediate; int /*<<< orphan*/  pm_indicated; int /*<<< orphan*/  supp_reason; int /*<<< orphan*/  rts_count; int /*<<< orphan*/  frame_count; int /*<<< orphan*/  phy_stat; int /*<<< orphan*/  seq; scalar_t__ cookie; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct b43legacy_txstatus_log txstatlog; } ;

/* Variables and functions */
 int B43legacy_NR_LOGGED_TXSTATUS ; 
 int /*<<< orphan*/  fappend (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t txstat_read_file(struct b43legacy_wldev *dev, char *buf, size_t bufsize)
{
	struct b43legacy_txstatus_log *log = &dev->dfsentry->txstatlog;
	ssize_t count = 0;
	unsigned long flags;
	int i, idx;
	struct b43legacy_txstatus *stat;

	spin_lock_irqsave(&log->lock, flags);
	if (log->end < 0) {
		fappend("Nothing transmitted, yet\n");
		goto out_unlock;
	}
	fappend("b43legacy TX status reports:\n\n"
		"index | cookie | seq | phy_stat | frame_count | "
		"rts_count | supp_reason | pm_indicated | "
		"intermediate | for_ampdu | acked\n" "---\n");
	i = log->end + 1;
	idx = 0;
	while (1) {
		if (i == B43legacy_NR_LOGGED_TXSTATUS)
			i = 0;
		stat = &(log->log[i]);
		if (stat->cookie) {
			fappend("%03d | "
				"0x%04X | 0x%04X | 0x%02X | "
				"0x%X | 0x%X | "
				"%u | %u | "
				"%u | %u | %u\n",
				idx,
				stat->cookie, stat->seq, stat->phy_stat,
				stat->frame_count, stat->rts_count,
				stat->supp_reason, stat->pm_indicated,
				stat->intermediate, stat->for_ampdu,
				stat->acked);
			idx++;
		}
		if (i == log->end)
			break;
		i++;
	}
out_unlock:
	spin_unlock_irqrestore(&log->lock, flags);

	return count;
}