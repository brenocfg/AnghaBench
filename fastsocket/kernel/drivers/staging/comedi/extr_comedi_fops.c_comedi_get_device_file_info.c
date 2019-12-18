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
struct comedi_device_file_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int COMEDI_NUM_MINORS ; 
 struct comedi_device_file_info** comedi_file_info_table ; 
 int /*<<< orphan*/  comedi_file_info_table_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct comedi_device_file_info *comedi_get_device_file_info(unsigned minor)
{
	unsigned long flags;
	struct comedi_device_file_info *info;

	BUG_ON(minor >= COMEDI_NUM_MINORS);
	spin_lock_irqsave(&comedi_file_info_table_lock, flags);
	info = comedi_file_info_table[minor];
	spin_unlock_irqrestore(&comedi_file_info_table_lock, flags);
	return info;
}