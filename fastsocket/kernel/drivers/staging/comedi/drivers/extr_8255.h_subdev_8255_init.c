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
struct comedi_subdevice {int /*<<< orphan*/  type; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_UNUSED ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static inline int subdev_8255_init(struct comedi_device *dev,
				   struct comedi_subdevice *s, void *x,
				   unsigned long y)
{
	printk("8255 support not configured -- disabling subdevice\n");

	s->type = COMEDI_SUBD_UNUSED;

	return 0;
}