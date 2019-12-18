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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ni_old_get_pfi_routing (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int ni_old_set_pfi_routing(struct comedi_device *dev, unsigned chan,
				  unsigned source)
{
	/*  pre-m-series boards have fixed signals on pfi pins */
	if (source != ni_old_get_pfi_routing(dev, chan))
		return -EINVAL;
	return 2;
}