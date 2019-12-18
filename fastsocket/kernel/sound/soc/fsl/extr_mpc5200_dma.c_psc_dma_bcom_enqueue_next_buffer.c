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
struct psc_dma_stream {scalar_t__ period_bytes; scalar_t__ period_next_pt; scalar_t__ period_end; scalar_t__ period_start; int /*<<< orphan*/  bcom_task; } ;
struct bcom_bd {scalar_t__ status; scalar_t__* data; } ;

/* Variables and functions */
 struct bcom_bd* bcom_prepare_next_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_submit_next_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psc_dma_bcom_enqueue_next_buffer(struct psc_dma_stream *s)
{
	struct bcom_bd *bd;

	/* Prepare and enqueue the next buffer descriptor */
	bd = bcom_prepare_next_buffer(s->bcom_task);
	bd->status = s->period_bytes;
	bd->data[0] = s->period_next_pt;
	bcom_submit_next_buffer(s->bcom_task, NULL);

	/* Update for next period */
	s->period_next_pt += s->period_bytes;
	if (s->period_next_pt >= s->period_end)
		s->period_next_pt = s->period_start;
}