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
struct comedi_subdevice {scalar_t__ private; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ have_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 TYPE_1__* subdevpriv ; 

void subdev_700_cleanup(struct comedi_device *dev, struct comedi_subdevice *s)
{
	if (s->private) {
		if (subdevpriv->have_irq) {
		}

		kfree(s->private);
	}
}