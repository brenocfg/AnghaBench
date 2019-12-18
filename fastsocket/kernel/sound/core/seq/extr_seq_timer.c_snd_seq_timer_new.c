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
struct snd_seq_timer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_seq_timer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  snd_seq_timer_defaults (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  snd_seq_timer_reset (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct snd_seq_timer *snd_seq_timer_new(void)
{
	struct snd_seq_timer *tmr;
	
	tmr = kzalloc(sizeof(*tmr), GFP_KERNEL);
	if (tmr == NULL) {
		snd_printd("malloc failed for snd_seq_timer_new() \n");
		return NULL;
	}
	spin_lock_init(&tmr->lock);

	/* reset setup to defaults */
	snd_seq_timer_defaults(tmr);
	
	/* reset time */
	snd_seq_timer_reset(tmr);
	
	return tmr;
}