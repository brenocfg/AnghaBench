#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ni_private {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/  soft_reg_copy_lock; int /*<<< orphan*/  window_lock; } ;

/* Variables and functions */
 int alloc_private (struct comedi_device*,int) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ni_alloc_private(struct comedi_device *dev)
{
	int ret;

	ret = alloc_private(dev, sizeof(struct ni_private));
	if (ret < 0)
		return ret;

	spin_lock_init(&devpriv->window_lock);
	spin_lock_init(&devpriv->soft_reg_copy_lock);
	spin_lock_init(&devpriv->mite_channel_lock);

	return 0;
}