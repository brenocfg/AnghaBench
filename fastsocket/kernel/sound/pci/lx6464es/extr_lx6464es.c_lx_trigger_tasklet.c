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
struct lx6464es {int /*<<< orphan*/  lock; int /*<<< orphan*/  playback_stream; int /*<<< orphan*/  capture_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  lx_trigger_tasklet_dispatch_stream (struct lx6464es*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lx_trigger_tasklet(unsigned long data)
{
	struct lx6464es *chip = (struct lx6464es *)data;
	unsigned long flags;

	snd_printdd("->lx_trigger_tasklet\n");

	spin_lock_irqsave(&chip->lock, flags);
	lx_trigger_tasklet_dispatch_stream(chip, &chip->capture_stream);
	lx_trigger_tasklet_dispatch_stream(chip, &chip->playback_stream);
	spin_unlock_irqrestore(&chip->lock, flags);
}