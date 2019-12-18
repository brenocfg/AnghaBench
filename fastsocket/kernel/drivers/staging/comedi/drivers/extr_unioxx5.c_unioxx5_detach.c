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
struct unioxx5_subd_priv {int /*<<< orphan*/  usp_iobase; } ;
struct comedi_subdevice {struct unioxx5_subd_priv* private; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIOXX5_SIZE ; 
 int /*<<< orphan*/  kfree (struct unioxx5_subd_priv*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unioxx5_detach(struct comedi_device *dev)
{
	int i;
	struct comedi_subdevice *subdev;
	struct unioxx5_subd_priv *usp;

	for (i = 0; i < dev->n_subdevices; i++) {
		subdev = &dev->subdevices[i];
		usp = subdev->private;
		release_region(usp->usp_iobase, UNIOXX5_SIZE);
		kfree(subdev->private);
	}

	return 0;
}