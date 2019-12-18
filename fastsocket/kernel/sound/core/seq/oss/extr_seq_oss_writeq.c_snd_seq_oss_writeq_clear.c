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
struct snd_seq_remove_events {int /*<<< orphan*/  remove_mode; } ;
struct seq_oss_writeq {int /*<<< orphan*/  dp; } ;
typedef  int /*<<< orphan*/  reset ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_REMOVE_EVENTS ; 
 int /*<<< orphan*/  SNDRV_SEQ_REMOVE_OUTPUT ; 
 int /*<<< orphan*/  memset (struct snd_seq_remove_events*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_oss_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_remove_events*) ; 
 int /*<<< orphan*/  snd_seq_oss_writeq_wakeup (struct seq_oss_writeq*,int /*<<< orphan*/ ) ; 

void
snd_seq_oss_writeq_clear(struct seq_oss_writeq *q)
{
	struct snd_seq_remove_events reset;

	memset(&reset, 0, sizeof(reset));
	reset.remove_mode = SNDRV_SEQ_REMOVE_OUTPUT; /* remove all */
	snd_seq_oss_control(q->dp, SNDRV_SEQ_IOCTL_REMOVE_EVENTS, &reset);

	/* wake up sleepers if any */
	snd_seq_oss_writeq_wakeup(q, 0);
}