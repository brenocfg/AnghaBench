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
struct comedi_device_file_info {struct comedi_device* device; } ;
struct comedi_device {int /*<<< orphan*/  attached; } ;

/* Variables and functions */
 unsigned int COMEDI_NUM_MINORS ; 
 struct comedi_device_file_info* comedi_get_device_file_info (unsigned int) ; 

void *comedi_open_old(unsigned int minor)
{
	struct comedi_device_file_info *dev_file_info;
	struct comedi_device *dev;

	if (minor >= COMEDI_NUM_MINORS)
		return NULL;

	dev_file_info = comedi_get_device_file_info(minor);
	if (dev_file_info == NULL)
		return NULL;
	dev = dev_file_info->device;

	if (dev == NULL || !dev->attached)
		return NULL;

	return (void *)dev;
}