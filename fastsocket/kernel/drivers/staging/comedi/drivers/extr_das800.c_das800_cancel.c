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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ count; scalar_t__ forever; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_das800 (struct comedi_device*) ; 

__attribute__((used)) static int das800_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	devpriv->forever = 0;
	devpriv->count = 0;
	disable_das800(dev);
	return 0;
}