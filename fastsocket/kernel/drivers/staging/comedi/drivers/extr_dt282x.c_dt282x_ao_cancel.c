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
struct TYPE_2__ {scalar_t__ supcsr; scalar_t__ dacsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT2821_DACINIT ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  dt282x_disable_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  update_dacsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_supcsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt282x_ao_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	dt282x_disable_dma(dev);

	devpriv->dacsr = 0;
	update_dacsr(0);

	devpriv->supcsr = 0;
	update_supcsr(DT2821_DACINIT);

	return 0;
}