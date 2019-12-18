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
struct seq_oss_readq {unsigned long input_time; int /*<<< orphan*/  midi_sleep; scalar_t__ tail; scalar_t__ head; scalar_t__ qlen; } ;

/* Variables and functions */
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void
snd_seq_oss_readq_clear(struct seq_oss_readq *q)
{
	if (q->qlen) {
		q->qlen = 0;
		q->head = q->tail = 0;
	}
	/* if someone sleeping, wake'em up */
	if (waitqueue_active(&q->midi_sleep))
		wake_up(&q->midi_sleep);
	q->input_time = (unsigned long)-1;
}