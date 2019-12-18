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
struct page {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct ata_queued_cmd {scalar_t__ curbytes; scalar_t__ nbytes; scalar_t__ sect_size; unsigned int cursg_ofs; TYPE_3__* cursg; int /*<<< orphan*/  dev; TYPE_1__ tf; struct ata_port* ap; } ;
struct ata_port {TYPE_2__* ops; int /*<<< orphan*/  hsm_task_state; } ;
struct TYPE_8__ {unsigned int offset; unsigned int length; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* sff_data_xfer ) (int /*<<< orphan*/ ,unsigned char*,scalar_t__,int) ;} ;

/* Variables and functions */
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  DPRINTK (char*,char*) ; 
 int /*<<< orphan*/  HSM_ST_LAST ; 
 int /*<<< orphan*/  KM_IRQ0 ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct page* nth_page (struct page*,unsigned int) ; 
 unsigned char* page_address (struct page*) ; 
 TYPE_3__* sg_next (TYPE_3__*) ; 
 struct page* sg_page (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned char*,scalar_t__,int) ; 

__attribute__((used)) static void ata_pio_sector(struct ata_queued_cmd *qc)
{
	int do_write = (qc->tf.flags & ATA_TFLAG_WRITE);
	struct ata_port *ap = qc->ap;
	struct page *page;
	unsigned int offset;
	unsigned char *buf;

	if (qc->curbytes == qc->nbytes - qc->sect_size)
		ap->hsm_task_state = HSM_ST_LAST;

	page = sg_page(qc->cursg);
	offset = qc->cursg->offset + qc->cursg_ofs;

	/* get the current page and offset */
	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;

	DPRINTK("data %s\n", qc->tf.flags & ATA_TFLAG_WRITE ? "write" : "read");

	if (PageHighMem(page)) {
		unsigned long flags;

		/* FIXME: use a bounce buffer */
		local_irq_save(flags);
		buf = kmap_atomic(page, KM_IRQ0);

		/* do the actual data transfer */
		ap->ops->sff_data_xfer(qc->dev, buf + offset, qc->sect_size,
				       do_write);

		kunmap_atomic(buf, KM_IRQ0);
		local_irq_restore(flags);
	} else {
		buf = page_address(page);
		ap->ops->sff_data_xfer(qc->dev, buf + offset, qc->sect_size,
				       do_write);
	}

	if (!do_write && !PageSlab(page))
		flush_dcache_page(page);

	qc->curbytes += qc->sect_size;
	qc->cursg_ofs += qc->sect_size;

	if (qc->cursg_ofs == qc->cursg->length) {
		qc->cursg = sg_next(qc->cursg);
		qc->cursg_ofs = 0;
	}
}