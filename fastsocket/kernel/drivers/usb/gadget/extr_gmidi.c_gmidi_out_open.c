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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct gmidi_device {struct snd_rawmidi_substream* out_substream; } ;
struct TYPE_2__ {struct gmidi_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (struct gmidi_device*,char*) ; 

__attribute__((used)) static int gmidi_out_open(struct snd_rawmidi_substream *substream)
{
	struct gmidi_device *dev = substream->rmidi->private_data;

	VDBG(dev, "gmidi_out_open\n");
	dev->out_substream = substream;
	return 0;
}