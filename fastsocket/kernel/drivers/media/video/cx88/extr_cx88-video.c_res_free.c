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
struct cx88_core {int /*<<< orphan*/  lock; } ;
struct cx8800_fh {unsigned int resources; } ;
struct cx8800_dev {unsigned int resources; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void res_free(struct cx8800_dev *dev, struct cx8800_fh *fh, unsigned int bits)
{
	struct cx88_core *core = dev->core;
	BUG_ON((fh->resources & bits) != bits);

	mutex_lock(&core->lock);
	fh->resources  &= ~bits;
	dev->resources &= ~bits;
	dprintk(1,"res: put %d\n",bits);
	mutex_unlock(&core->lock);
}