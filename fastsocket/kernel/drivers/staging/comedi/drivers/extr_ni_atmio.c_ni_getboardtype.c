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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int device_id; } ;

/* Variables and functions */
 int n_ni_boards ; 
 TYPE_1__* ni_boards ; 
 int ni_read_eeprom (struct comedi_device*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int ni_getboardtype(struct comedi_device *dev)
{
	int device_id = ni_read_eeprom(dev, 511);
	int i;

	for (i = 0; i < n_ni_boards; i++) {
		if (ni_boards[i].device_id == device_id) {
			return i;
		}
	}
	if (device_id == 255) {
		printk(" can't find board\n");
	} else if (device_id == 0) {
		printk(" EEPROM read error (?) or device not found\n");
	} else {
		printk(" unknown device ID %d -- contact author\n", device_id);
	}
	return -1;
}