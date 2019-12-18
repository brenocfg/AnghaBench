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
struct gemtek {int /*<<< orphan*/  lock; int /*<<< orphan*/  io; int /*<<< orphan*/  lastfreq; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHORT_DELAY ; 
 int /*<<< orphan*/  gemtek_setfreq (struct gemtek*,int /*<<< orphan*/ ) ; 
 scalar_t__ hardmute ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gemtek_unmute(struct gemtek *gt)
{
	int i;

	gt->muted = 0;
	if (hardmute) {
		/* Turn PLL back on. */
		gemtek_setfreq(gt, gt->lastfreq);
		return;
	}
	mutex_lock(&gt->lock);

	i = inb_p(gt->io);
	outb_p(i >> 5, gt->io);
	udelay(SHORT_DELAY);

	mutex_unlock(&gt->lock);
}