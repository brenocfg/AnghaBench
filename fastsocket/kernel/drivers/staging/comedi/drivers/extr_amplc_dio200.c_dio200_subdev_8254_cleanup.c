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
struct dio200_subdev_intr {int dummy; } ;
struct comedi_subdevice {struct dio200_subdev_intr* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dio200_subdev_intr*) ; 

__attribute__((used)) static void
dio200_subdev_8254_cleanup(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	struct dio200_subdev_intr *subpriv = s->private;

	if (subpriv) {
		kfree(subpriv);
	}
}