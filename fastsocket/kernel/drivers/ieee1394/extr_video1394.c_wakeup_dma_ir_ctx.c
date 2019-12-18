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
struct dma_iso_ctx {int num_desc; int nb_cmd; size_t* buffer_prg_assignment; int buf_size; int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma; int /*<<< orphan*/ * buffer_time; int /*<<< orphan*/ * buffer_status; TYPE_1__** ir_prg; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO1394_BUFFER_READY ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_region_sync_for_cpu (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_ir_status (struct dma_iso_ctx*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wakeup_dma_ir_ctx(unsigned long l)
{
	struct dma_iso_ctx *d = (struct dma_iso_ctx *) l;
	int i;

	spin_lock(&d->lock);

	for (i = 0; i < d->num_desc; i++) {
		if (d->ir_prg[i][d->nb_cmd-1].status & cpu_to_le32(0xFFFF0000)) {
			reset_ir_status(d, i);
			d->buffer_status[d->buffer_prg_assignment[i]] = VIDEO1394_BUFFER_READY;
			do_gettimeofday(&d->buffer_time[d->buffer_prg_assignment[i]]);
			dma_region_sync_for_cpu(&d->dma,
				d->buffer_prg_assignment[i] * d->buf_size,
				d->buf_size);
		}
	}

	spin_unlock(&d->lock);

	if (waitqueue_active(&d->waitq))
		wake_up_interruptible(&d->waitq);
}