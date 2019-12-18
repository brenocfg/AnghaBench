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
struct comedi_device_file_info {TYPE_1__* device; struct comedi_subdevice* read_subdevice; } ;
struct TYPE_2__ {struct comedi_subdevice* read_subdev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct comedi_subdevice *comedi_get_read_subdevice(const struct
								 comedi_device_file_info
								 *info)
{
	if (info->read_subdevice)
		return info->read_subdevice;
	if (info->device == NULL)
		return NULL;
	return info->device->read_subdev;
}