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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct gmidi_device {TYPE_2__ in_port; struct snd_rawmidi_substream* in_substream; } ;
struct TYPE_3__ {struct gmidi_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_UNKNOWN ; 
 int /*<<< orphan*/  VDBG (struct gmidi_device*,char*) ; 

__attribute__((used)) static int gmidi_in_open(struct snd_rawmidi_substream *substream)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_in_open\n");
	dev->in_substream = substream;
	dev->in_port.state = STATE_UNKNOWN;
	return 0;
}