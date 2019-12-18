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
 int get_resources (struct comedi_device*,unsigned int,unsigned char) ; 

__attribute__((used)) static inline int get_one_resource(struct comedi_device *dev,
				   unsigned int resource, unsigned char owner)
{
	return get_resources(dev, (1U << resource), owner);
}