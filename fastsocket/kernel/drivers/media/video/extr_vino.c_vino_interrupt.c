#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_9__ {unsigned int line_count; unsigned int page_index; unsigned int field_counter; unsigned int start_desc_tbl; unsigned int next_4_desc; } ;
struct TYPE_8__ {int field_counter; } ;
struct TYPE_13__ {int intr_status; int control; TYPE_2__ a; TYPE_1__ b; } ;
struct TYPE_10__ {unsigned int frame_counter; int skip; int /*<<< orphan*/  timestamp; } ;
struct TYPE_12__ {int field; unsigned int line_size; TYPE_3__ int_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  vino_lock; TYPE_5__ b; TYPE_5__ a; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int VINO_CTRL_A_INT ; 
 int VINO_CTRL_B_INT ; 
 int VINO_INTSTAT_A ; 
 int VINO_INTSTAT_A_EOF ; 
 int VINO_INTSTAT_B ; 
 int VINO_INTSTAT_B_EOF ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 TYPE_7__* vino ; 
 int /*<<< orphan*/  vino_clear_interrupt (TYPE_5__*) ; 
 int /*<<< orphan*/  vino_dma_stop (TYPE_5__*) ; 
 TYPE_4__* vino_drvdata ; 
 int /*<<< orphan*/  vino_tasklet_a ; 
 int /*<<< orphan*/  vino_tasklet_b ; 

__attribute__((used)) static irqreturn_t vino_interrupt(int irq, void *dev_id)
{
	u32 ctrl, intr;
	unsigned int fc_a, fc_b;
	int handled_a = 0, skip_a = 0, done_a = 0;
	int handled_b = 0, skip_b = 0, done_b = 0;

#ifdef VINO_DEBUG_INT
	int loop = 0;
	unsigned int line_count = vino->a.line_count,
		page_index = vino->a.page_index,
		field_counter = vino->a.field_counter,
		start_desc_tbl = vino->a.start_desc_tbl,
		next_4_desc = vino->a.next_4_desc;
	unsigned int line_count_2,
		page_index_2,
		field_counter_2,
		start_desc_tbl_2,
		next_4_desc_2;
#endif

	spin_lock(&vino_drvdata->vino_lock);

	while ((intr = vino->intr_status)) {
		fc_a = vino->a.field_counter >> 1;
		fc_b = vino->b.field_counter >> 1;

		/* handle error-interrupts in some special way ?
		 * --> skips frames */
		if (intr & VINO_INTSTAT_A) {
			if (intr & VINO_INTSTAT_A_EOF) {
				vino_drvdata->a.field++;
				if (vino_drvdata->a.field > 1) {
					vino_dma_stop(&vino_drvdata->a);
					vino_clear_interrupt(&vino_drvdata->a);
					vino_drvdata->a.field = 0;
					done_a = 1;
				} else {
					if (vino->a.page_index
					    != vino_drvdata->a.line_size) {
						vino->a.line_count = 0;
						vino->a.page_index =
							vino_drvdata->
							a.line_size;
						vino->a.next_4_desc =
							vino->a.start_desc_tbl;
					}
				}
				dprintk("channel A end-of-field "
					"interrupt: %04x\n", intr);
			} else {
				vino_dma_stop(&vino_drvdata->a);
				vino_clear_interrupt(&vino_drvdata->a);
				vino_drvdata->a.field = 0;
				skip_a = 1;
				dprintk("channel A error interrupt: %04x\n",
					intr);
			}

#ifdef VINO_DEBUG_INT
			line_count_2 = vino->a.line_count;
			page_index_2 = vino->a.page_index;
			field_counter_2 = vino->a.field_counter;
			start_desc_tbl_2 = vino->a.start_desc_tbl;
			next_4_desc_2 = vino->a.next_4_desc;

			printk("intr = %04x, loop = %d, field = %d\n",
			       intr, loop, vino_drvdata->a.field);
			printk("1- line count = %04d, page index = %04d, "
			       "start = %08x, next = %08x\n"
			       "   fieldc = %d, framec = %d\n",
			       line_count, page_index, start_desc_tbl,
			       next_4_desc, field_counter, fc_a);
			printk("12-line count = %04d, page index = %04d, "
			       "   start = %08x, next = %08x\n",
			       line_count_2, page_index_2, start_desc_tbl_2,
			       next_4_desc_2);

			if (done_a)
				printk("\n");
#endif
		}

		if (intr & VINO_INTSTAT_B) {
			if (intr & VINO_INTSTAT_B_EOF) {
				vino_drvdata->b.field++;
				if (vino_drvdata->b.field > 1) {
					vino_dma_stop(&vino_drvdata->b);
					vino_clear_interrupt(&vino_drvdata->b);
					vino_drvdata->b.field = 0;
					done_b = 1;
				}
				dprintk("channel B end-of-field "
					"interrupt: %04x\n", intr);
			} else {
				vino_dma_stop(&vino_drvdata->b);
				vino_clear_interrupt(&vino_drvdata->b);
				vino_drvdata->b.field = 0;
				skip_b = 1;
				dprintk("channel B error interrupt: %04x\n",
					intr);
			}
		}

		/* Always remember to clear interrupt status.
		 * Disable VINO interrupts while we do this. */
		ctrl = vino->control;
		vino->control = ctrl & ~(VINO_CTRL_A_INT | VINO_CTRL_B_INT);
		vino->intr_status = ~intr;
		vino->control = ctrl;

		spin_unlock(&vino_drvdata->vino_lock);

		if ((!handled_a) && (done_a || skip_a)) {
			if (!skip_a) {
				do_gettimeofday(&vino_drvdata->
						a.int_data.timestamp);
				vino_drvdata->a.int_data.frame_counter = fc_a;
			}
			vino_drvdata->a.int_data.skip = skip_a;

			dprintk("channel A %s, interrupt: %d\n",
				skip_a ? "skipping frame" : "frame done",
				intr);
			tasklet_hi_schedule(&vino_tasklet_a);
			handled_a = 1;
		}

		if ((!handled_b) && (done_b || skip_b)) {
			if (!skip_b) {
				do_gettimeofday(&vino_drvdata->
						b.int_data.timestamp);
				vino_drvdata->b.int_data.frame_counter = fc_b;
			}
			vino_drvdata->b.int_data.skip = skip_b;

			dprintk("channel B %s, interrupt: %d\n",
				skip_b ? "skipping frame" : "frame done",
				intr);
			tasklet_hi_schedule(&vino_tasklet_b);
			handled_b = 1;
		}

#ifdef VINO_DEBUG_INT
		loop++;
#endif
		spin_lock(&vino_drvdata->vino_lock);
	}

	spin_unlock(&vino_drvdata->vino_lock);

	return IRQ_HANDLED;
}