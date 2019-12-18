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
struct snd_line6_midi {int /*<<< orphan*/  midibuf_out; int /*<<< orphan*/  midibuf_in; TYPE_1__* line6; } ;
struct snd_device {struct snd_line6_midi* device_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifcdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_midi_mask_receive ; 
 int /*<<< orphan*/  dev_attr_midi_mask_transmit ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  midibuf_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_line6_midi_free(struct snd_device *device)
{
	struct snd_line6_midi *line6midi = device->device_data;
	device_remove_file(line6midi->line6->ifcdev, &dev_attr_midi_mask_transmit);
	device_remove_file(line6midi->line6->ifcdev, &dev_attr_midi_mask_receive);
	midibuf_destroy(&line6midi->midibuf_in);
	midibuf_destroy(&line6midi->midibuf_out);
	return 0;
}