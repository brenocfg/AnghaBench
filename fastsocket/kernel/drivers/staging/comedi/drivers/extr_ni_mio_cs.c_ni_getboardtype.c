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
struct pcmcia_device {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int device_id; } ;

/* Variables and functions */
 int get_prodid (struct comedi_device*,struct pcmcia_device*) ; 
 int n_ni_boards ; 
 TYPE_1__* ni_boards ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int ni_getboardtype(struct comedi_device *dev,
			   struct pcmcia_device *link)
{
	int id;
	int i;

	id = get_prodid(dev, link);

	for (i = 0; i < n_ni_boards; i++) {
		if (ni_boards[i].device_id == id) {
			return i;
		}
	}

	printk("unknown board 0x%04x -- pretend it is a ", id);

	return 0;
}