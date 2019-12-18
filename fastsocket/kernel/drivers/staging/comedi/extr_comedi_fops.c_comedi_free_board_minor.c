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
struct comedi_device_file_info {int /*<<< orphan*/  minor; scalar_t__ class_dev; struct comedi_device_file_info* device; } ;
struct comedi_device {int /*<<< orphan*/  minor; scalar_t__ class_dev; struct comedi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_class ; 
 int /*<<< orphan*/  comedi_device_cleanup (struct comedi_device_file_info*) ; 
 struct comedi_device_file_info** comedi_file_info_table ; 
 int /*<<< orphan*/  comedi_file_info_table_lock ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct comedi_device_file_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void comedi_free_board_minor(unsigned minor)
{
	unsigned long flags;
	struct comedi_device_file_info *info;

	BUG_ON(minor >= COMEDI_NUM_BOARD_MINORS);
	spin_lock_irqsave(&comedi_file_info_table_lock, flags);
	info = comedi_file_info_table[minor];
	comedi_file_info_table[minor] = NULL;
	spin_unlock_irqrestore(&comedi_file_info_table_lock, flags);

	if (info) {
		struct comedi_device *dev = info->device;
		if (dev) {
			if (dev->class_dev) {
				device_destroy(comedi_class,
					       MKDEV(COMEDI_MAJOR, dev->minor));
			}
			comedi_device_cleanup(dev);
			kfree(dev);
		}
		kfree(info);
	}
}