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
struct gemtek {int verified; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int GEMTEK_NS ; 
 int /*<<< orphan*/  SHORT_DELAY ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gemtek_verify(struct gemtek *gt, int port)
{
	int i, q;

	if (gt->verified == port)
		return 1;

	mutex_lock(&gt->lock);

	q = inb_p(port);	/* Read bus contents before probing. */
	/* Try to turn on CE, CK and DA respectively and check if card responds
	   properly. */
	for (i = 0; i < 3; ++i) {
		outb_p(1 << i, port);
		udelay(SHORT_DELAY);

		if ((inb_p(port) & (~GEMTEK_NS)) != (0x17 | (1 << (i + 5)))) {
			mutex_unlock(&gt->lock);
			return 0;
		}
	}
	outb_p(q >> 5, port);	/* Write bus contents back. */
	udelay(SHORT_DELAY);

	mutex_unlock(&gt->lock);
	gt->verified = port;

	return 1;
}