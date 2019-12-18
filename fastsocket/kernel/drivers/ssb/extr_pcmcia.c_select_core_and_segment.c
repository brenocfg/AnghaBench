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
typedef  int u8 ;
typedef  int u16 ;
struct ssb_device {struct ssb_bus* bus; } ;
struct ssb_bus {int mapped_pcmcia_seg; struct ssb_device* mapped_device; } ;

/* Variables and functions */
 int ssb_pcmcia_switch_core (struct ssb_bus*,struct ssb_device*) ; 
 int ssb_pcmcia_switch_segment (struct ssb_bus*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int select_core_and_segment(struct ssb_device *dev,
				   u16 *offset)
{
	struct ssb_bus *bus = dev->bus;
	int err;
	u8 need_segment;

	if (*offset >= 0x800) {
		*offset -= 0x800;
		need_segment = 1;
	} else
		need_segment = 0;

	if (unlikely(dev != bus->mapped_device)) {
		err = ssb_pcmcia_switch_core(bus, dev);
		if (unlikely(err))
			return err;
	}
	if (unlikely(need_segment != bus->mapped_pcmcia_seg)) {
		err = ssb_pcmcia_switch_segment(bus, need_segment);
		if (unlikely(err))
			return err;
	}

	return 0;
}