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
struct snd_kcontrol {int /*<<< orphan*/  put; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_POWERDOWN ; 
 int ENOENT ; 
 int /*<<< orphan*/  bind_hp_volsw_put ; 
 struct snd_kcontrol* ctl_find (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hp_master_mute_sw_put ; 
 int /*<<< orphan*/  snd_ac97_remove_ctl (struct snd_ac97*,char*,char*) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tune_hp_mute_led(struct snd_ac97 *ac97)
{
	struct snd_kcontrol *msw = ctl_find(ac97, "Master Playback Switch", NULL);
	struct snd_kcontrol *mvol = ctl_find(ac97, "Master Playback Volume", NULL);
	if (! msw || ! mvol)
		return -ENOENT;
	msw->put = hp_master_mute_sw_put;
	mvol->put = bind_hp_volsw_put;
	snd_ac97_remove_ctl(ac97, "External Amplifier", NULL);
	snd_ac97_remove_ctl(ac97, "Headphone Playback", "Switch");
	snd_ac97_remove_ctl(ac97, "Headphone Playback", "Volume");
	snd_ac97_update_bits(ac97, AC97_POWERDOWN, 0x8000, 0x8000); /* mute LED on */
	return 0;
}