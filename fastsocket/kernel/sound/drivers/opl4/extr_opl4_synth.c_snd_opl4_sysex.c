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
struct snd_opl4 {int dummy; } ;
struct snd_midi_channel_set {int dummy; } ;

/* Variables and functions */
 int SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME ; 
 int /*<<< orphan*/  snd_opl4_do_for_all (struct snd_opl4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_update_volume ; 

void snd_opl4_sysex(void *private_data, unsigned char *buf, int len,
		    int parsed, struct snd_midi_channel_set *chset)
{
	struct snd_opl4 *opl4 = private_data;

	if (parsed == SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME)
		snd_opl4_do_for_all(opl4, snd_opl4_update_volume);
}