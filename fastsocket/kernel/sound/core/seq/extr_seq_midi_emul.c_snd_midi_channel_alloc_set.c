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
struct snd_midi_channel_set {int max_channels; int /*<<< orphan*/ * private_data; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_midi_channel_set* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_midi_channel_init_set (int) ; 

struct snd_midi_channel_set *snd_midi_channel_alloc_set(int n)
{
	struct snd_midi_channel_set *chset;

	chset = kmalloc(sizeof(*chset), GFP_KERNEL);
	if (chset) {
		chset->channels = snd_midi_channel_init_set(n);
		chset->private_data = NULL;
		chset->max_channels = n;
	}
	return chset;
}