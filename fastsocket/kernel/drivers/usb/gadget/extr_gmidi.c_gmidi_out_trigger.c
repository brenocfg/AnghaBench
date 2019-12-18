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
struct snd_rawmidi_substream {int /*<<< orphan*/  number; TYPE_1__* rmidi; } ;
struct gmidi_device {int /*<<< orphan*/  out_triggered; } ;
struct TYPE_2__ {struct gmidi_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (struct gmidi_device*,char*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmidi_out_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_out_trigger %d\n", up);
	if (up) {
		set_bit(substream->number, &dev->out_triggered);
	} else {
		clear_bit(substream->number, &dev->out_triggered);
	}
}