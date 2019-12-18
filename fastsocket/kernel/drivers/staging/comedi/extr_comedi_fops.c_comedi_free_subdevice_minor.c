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
struct comedi_subdevice {size_t minor; int /*<<< orphan*/ * class_dev; } ;
struct comedi_device_file_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t COMEDI_FIRST_SUBDEVICE_MINOR ; 
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 size_t COMEDI_NUM_MINORS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  comedi_class ; 
 struct comedi_device_file_info** comedi_file_info_table ; 
 int /*<<< orphan*/  comedi_file_info_table_lock ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct comedi_device_file_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void comedi_free_subdevice_minor(struct comedi_subdevice *s)
{
	unsigned long flags;
	struct comedi_device_file_info *info;

	if (s == NULL)
		return;
	if (s->minor < 0)
		return;

	BUG_ON(s->minor >= COMEDI_NUM_MINORS);
	BUG_ON(s->minor < COMEDI_FIRST_SUBDEVICE_MINOR);

	spin_lock_irqsave(&comedi_file_info_table_lock, flags);
	info = comedi_file_info_table[s->minor];
	comedi_file_info_table[s->minor] = NULL;
	spin_unlock_irqrestore(&comedi_file_info_table_lock, flags);

	if (s->class_dev) {
		device_destroy(comedi_class, MKDEV(COMEDI_MAJOR, s->minor));
		s->class_dev = NULL;
	}
	kfree(info);
}