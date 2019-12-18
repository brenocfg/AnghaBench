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
struct snd_rawmidi_substream {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* trigger ) (struct snd_rawmidi_substream*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_rawmidi_substream*,int) ; 

__attribute__((used)) static void snd_rawmidi_output_trigger_tasklet(unsigned long data)
{
	struct snd_rawmidi_substream *substream = (struct snd_rawmidi_substream *)data;
	substream->ops->trigger(substream, 1);
}