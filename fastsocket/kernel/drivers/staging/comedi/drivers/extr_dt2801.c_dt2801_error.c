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
 int EIO ; 
 int ETIME ; 
 int /*<<< orphan*/  dt2801_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int dt2801_error(struct comedi_device *dev, int stat)
{
	if (stat < 0) {
		if (stat == -ETIME) {
			printk("dt2801: timeout\n");
		} else {
			printk("dt2801: error %d\n", stat);
		}
		return stat;
	}
	printk("dt2801: error status 0x%02x, resetting...\n", stat);

	dt2801_reset(dev);
	dt2801_reset(dev);

	return -EIO;
}