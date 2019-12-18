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
struct seq_oss_readq {unsigned int qlen; int /*<<< orphan*/  midi_sleep; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

unsigned int
snd_seq_oss_readq_poll(struct seq_oss_readq *q, struct file *file, poll_table *wait)
{
	poll_wait(file, &q->midi_sleep, wait);
	return q->qlen;
}