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
struct rtrack2 {unsigned long curfreq; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; int /*<<< orphan*/  muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  one (struct rtrack2*) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero (struct rtrack2*) ; 

__attribute__((used)) static int rt_setfreq(struct rtrack2 *dev, unsigned long freq)
{
	int i;

	mutex_lock(&dev->lock);
	dev->curfreq = freq;
	freq = freq / 200 + 856;

	outb_p(0xc8, dev->io);
	outb_p(0xc9, dev->io);
	outb_p(0xc9, dev->io);

	for (i = 0; i < 10; i++)
		zero(dev);

	for (i = 14; i >= 0; i--)
		if (freq & (1 << i))
			one(dev);
		else
			zero(dev);

	outb_p(0xc8, dev->io);
	if (!dev->muted)
		outb_p(0, dev->io);

	mutex_unlock(&dev->lock);
	return 0;
}