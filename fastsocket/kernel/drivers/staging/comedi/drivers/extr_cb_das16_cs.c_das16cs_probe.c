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
struct pcmcia_device {int dummy; } ;
struct das16cs_board {int device_id; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 struct das16cs_board const* das16cs_boards ; 
 int get_prodid (struct comedi_device*,struct pcmcia_device*) ; 
 int n_boards ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static const struct das16cs_board *das16cs_probe(struct comedi_device *dev,
						 struct pcmcia_device *link)
{
	int id;
	int i;

	id = get_prodid(dev, link);

	for (i = 0; i < n_boards; i++) {
		if (das16cs_boards[i].device_id == id) {
			return das16cs_boards + i;
		}
	}

	printk("unknown board!\n");

	return NULL;
}