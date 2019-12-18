#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_4__ {int active; } ;
struct gmidi_device {int /*<<< orphan*/  tasklet; TYPE_2__ in_port; } ;
struct TYPE_3__ {struct gmidi_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (struct gmidi_device*,char*,int) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmidi_in_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_in_trigger %d\n", up);
	dev->in_port.active = up;
	if (up) {
		tasklet_hi_schedule(&dev->tasklet);
	}
}