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
struct saa7134_fh {unsigned int resources; } ;
struct saa7134_dev {unsigned int resources; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void res_free(struct saa7134_dev *dev, struct saa7134_fh *fh, unsigned int bits)
{
	BUG_ON((fh->resources & bits) != bits);

	mutex_lock(&dev->lock);
	fh->resources  &= ~bits;
	dev->resources &= ~bits;
	dprintk("res: put %d\n",bits);
	mutex_unlock(&dev->lock);
}