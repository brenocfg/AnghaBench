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
struct comedi_subdevice {int subdev_flags; } ;

/* Variables and functions */
 int SDF_LSAMPL ; 

__attribute__((used)) static inline unsigned int bytes_per_sample(const struct comedi_subdevice *subd)
{
	if (subd->subdev_flags & SDF_LSAMPL)
		return sizeof(unsigned int);
	else
		return sizeof(short);
}