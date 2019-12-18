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
struct seq_table {unsigned long seqid; int /*<<< orphan*/  orig_timeout; int /*<<< orphan*/  timeout; scalar_t__ inuse; } ;
typedef  TYPE_1__* ipmi_smi_t ;
struct TYPE_3__ {int /*<<< orphan*/  seq_lock; struct seq_table* seq_table; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GET_SEQ_FROM_MSGID (long,unsigned char,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int intf_start_seq_timer(ipmi_smi_t intf,
				long       msgid)
{
	int           rv = -ENODEV;
	unsigned long flags;
	unsigned char seq;
	unsigned long seqid;


	GET_SEQ_FROM_MSGID(msgid, seq, seqid);

	spin_lock_irqsave(&(intf->seq_lock), flags);
	/*
	 * We do this verification because the user can be deleted
	 * while a message is outstanding.
	 */
	if ((intf->seq_table[seq].inuse)
				&& (intf->seq_table[seq].seqid == seqid)) {
		struct seq_table *ent = &(intf->seq_table[seq]);
		ent->timeout = ent->orig_timeout;
		rv = 0;
	}
	spin_unlock_irqrestore(&(intf->seq_lock), flags);

	return rv;
}