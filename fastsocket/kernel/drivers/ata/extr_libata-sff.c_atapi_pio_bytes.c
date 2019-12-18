#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int nsect; unsigned int lbam; unsigned int lbah; } ;
struct TYPE_6__ {int flags; } ;
struct ata_queued_cmd {int /*<<< orphan*/  err_mask; TYPE_4__ result_tf; TYPE_2__ tf; struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  hsm_task_state; int /*<<< orphan*/  print_id; TYPE_3__* ops; } ;
struct ata_eh_info {int dummy; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* sff_tf_read ) (struct ata_port*,TYPE_4__*) ;} ;
struct TYPE_5__ {struct ata_eh_info eh_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_ERR_HSM ; 
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  HSM_ST_ERR ; 
 int /*<<< orphan*/  VPRINTK (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int __atapi_pio_bytes (struct ata_queued_cmd*,unsigned int) ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ata_sff_sync (struct ata_port*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void atapi_pio_bytes(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *dev = qc->dev;
	struct ata_eh_info *ehi = &dev->link->eh_info;
	unsigned int ireason, bc_lo, bc_hi, bytes;
	int i_write, do_write = (qc->tf.flags & ATA_TFLAG_WRITE) ? 1 : 0;

	/* Abuse qc->result_tf for temp storage of intermediate TF
	 * here to save some kernel stack usage.
	 * For normal completion, qc->result_tf is not relevant. For
	 * error, qc->result_tf is later overwritten by ata_qc_complete().
	 * So, the correctness of qc->result_tf is not affected.
	 */
	ap->ops->sff_tf_read(ap, &qc->result_tf);
	ireason = qc->result_tf.nsect;
	bc_lo = qc->result_tf.lbam;
	bc_hi = qc->result_tf.lbah;
	bytes = (bc_hi << 8) | bc_lo;

	/* shall be cleared to zero, indicating xfer of data */
	if (unlikely(ireason & (1 << 0)))
		goto atapi_check;

	/* make sure transfer direction matches expected */
	i_write = ((ireason & (1 << 1)) == 0) ? 1 : 0;
	if (unlikely(do_write != i_write))
		goto atapi_check;

	if (unlikely(!bytes))
		goto atapi_check;

	VPRINTK("ata%u: xfering %d bytes\n", ap->print_id, bytes);

	if (unlikely(__atapi_pio_bytes(qc, bytes)))
		goto err_out;
	ata_sff_sync(ap); /* flush */

	return;

 atapi_check:
	ata_ehi_push_desc(ehi, "ATAPI check failed (ireason=0x%x bytes=%u)",
			  ireason, bytes);
 err_out:
	qc->err_mask |= AC_ERR_HSM;
	ap->hsm_task_state = HSM_ST_ERR;
}