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
struct psc_dma_stream {scalar_t__ period_current_pt; scalar_t__ period_bytes; scalar_t__ period_end; scalar_t__ period_start; int /*<<< orphan*/  stream; scalar_t__ active; TYPE_1__* psc_dma; int /*<<< orphan*/  bcom_task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bcom_buffer_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_retrieve_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psc_dma_bcom_enqueue_next_buffer (struct psc_dma_stream*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t psc_dma_bcom_irq_rx(int irq, void *_psc_dma_stream)
{
	struct psc_dma_stream *s = _psc_dma_stream;

	spin_lock(&s->psc_dma->lock);
	/* For each finished period, dequeue the completed period buffer
	 * and enqueue a new one in it's place. */
	while (bcom_buffer_done(s->bcom_task)) {
		bcom_retrieve_buffer(s->bcom_task, NULL, NULL);

		s->period_current_pt += s->period_bytes;
		if (s->period_current_pt >= s->period_end)
			s->period_current_pt = s->period_start;

		psc_dma_bcom_enqueue_next_buffer(s);
	}
	spin_unlock(&s->psc_dma->lock);

	/* If the stream is active, then also inform the PCM middle layer
	 * of the period finished event. */
	if (s->active)
		snd_pcm_period_elapsed(s->stream);

	return IRQ_HANDLED;
}