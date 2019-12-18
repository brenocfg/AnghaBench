#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int field; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct vpfe_device {scalar_t__ cur_frm; scalar_t__ next_frm; int field_id; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; scalar_t__ field_off; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  started; TYPE_3__ fmt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_9__ {int (* getfid ) () ;int /*<<< orphan*/  (* setfbaddr ) (unsigned long) ;int /*<<< orphan*/  (* reset ) () ;} ;
struct TYPE_10__ {TYPE_4__ hw_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int V4L2_FIELD_NONE ; 
 int V4L2_FIELD_SEQ_TB ; 
 TYPE_5__* ccdc_dev ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 (unsigned long) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 unsigned long videobuf_to_dma_contig (scalar_t__) ; 
 int /*<<< orphan*/  vpfe_process_buffer_complete (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_schedule_next_buffer (struct vpfe_device*) ; 

__attribute__((used)) static irqreturn_t vpfe_isr(int irq, void *dev_id)
{
	struct vpfe_device *vpfe_dev = dev_id;
	enum v4l2_field field;
	unsigned long addr;
	int fid;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "\nStarting vpfe_isr...\n");
	field = vpfe_dev->fmt.fmt.pix.field;

	/* if streaming not started, don't do anything */
	if (!vpfe_dev->started)
		return IRQ_HANDLED;

	/* only for 6446 this will be applicable */
	if (NULL != ccdc_dev->hw_ops.reset)
		ccdc_dev->hw_ops.reset();

	if (field == V4L2_FIELD_NONE) {
		/* handle progressive frame capture */
		v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
			"frame format is progressive...\n");
		if (vpfe_dev->cur_frm != vpfe_dev->next_frm)
			vpfe_process_buffer_complete(vpfe_dev);
		return IRQ_HANDLED;
	}

	/* interlaced or TB capture check which field we are in hardware */
	fid = ccdc_dev->hw_ops.getfid();

	/* switch the software maintained field id */
	vpfe_dev->field_id ^= 1;
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "field id = %x:%x.\n",
		fid, vpfe_dev->field_id);
	if (fid == vpfe_dev->field_id) {
		/* we are in-sync here,continue */
		if (fid == 0) {
			/*
			 * One frame is just being captured. If the next frame
			 * is available, release the current frame and move on
			 */
			if (vpfe_dev->cur_frm != vpfe_dev->next_frm)
				vpfe_process_buffer_complete(vpfe_dev);
			/*
			 * based on whether the two fields are stored
			 * interleavely or separately in memory, reconfigure
			 * the CCDC memory address
			 */
			if (field == V4L2_FIELD_SEQ_TB) {
				addr =
				  videobuf_to_dma_contig(vpfe_dev->cur_frm);
				addr += vpfe_dev->field_off;
				ccdc_dev->hw_ops.setfbaddr(addr);
			}
			return IRQ_HANDLED;
		}
		/*
		 * if one field is just being captured configure
		 * the next frame get the next frame from the empty
		 * queue if no frame is available hold on to the
		 * current buffer
		 */
		spin_lock(&vpfe_dev->dma_queue_lock);
		if (!list_empty(&vpfe_dev->dma_queue) &&
		    vpfe_dev->cur_frm == vpfe_dev->next_frm)
			vpfe_schedule_next_buffer(vpfe_dev);
		spin_unlock(&vpfe_dev->dma_queue_lock);
	} else if (fid == 0) {
		/*
		 * out of sync. Recover from any hardware out-of-sync.
		 * May loose one frame
		 */
		vpfe_dev->field_id = fid;
	}
	return IRQ_HANDLED;
}