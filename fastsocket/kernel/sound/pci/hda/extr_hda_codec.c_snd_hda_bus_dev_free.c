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
struct snd_device {struct hda_bus* device_data; } ;
struct hda_bus {int shutdown; } ;

/* Variables and functions */
 int snd_hda_bus_free (struct hda_bus*) ; 

__attribute__((used)) static int snd_hda_bus_dev_free(struct snd_device *device)
{
	struct hda_bus *bus = device->device_data;
	bus->shutdown = 1;
	return snd_hda_bus_free(bus);
}