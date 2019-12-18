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
typedef  int u32 ;
struct ata_queued_cmd {int dummy; } ;
struct ata_port {int qc_active; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int __ffs (int) ; 
 int /*<<< orphan*/  ata_port_printk (struct ata_port*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ata_qc_complete (struct ata_queued_cmd*) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int ata_qc_complete_multiple(struct ata_port *ap, u32 qc_active)
{
	int nr_done = 0;
	u32 done_mask;

	done_mask = ap->qc_active ^ qc_active;

	if (unlikely(done_mask & qc_active)) {
		ata_port_printk(ap, KERN_ERR, "illegal qc_active transition "
				"(%08x->%08x)\n", ap->qc_active, qc_active);
		return -EINVAL;
	}

	while (done_mask) {
		struct ata_queued_cmd *qc;
		unsigned int tag = __ffs(done_mask);

		qc = ata_qc_from_tag(ap, tag);
		if (qc) {
			ata_qc_complete(qc);
			nr_done++;
		}
		done_mask &= ~(1 << tag);
	}

	return nr_done;
}