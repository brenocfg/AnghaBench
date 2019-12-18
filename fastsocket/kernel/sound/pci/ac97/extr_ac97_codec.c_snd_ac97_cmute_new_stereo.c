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
struct snd_kcontrol_new {int private_value; int /*<<< orphan*/  index; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct snd_ac97 {int flags; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 struct snd_kcontrol_new AC97_DOUBLE (char*,int,int,int,int,int) ; 
 struct snd_kcontrol_new AC97_SINGLE (char*,int,int,int,int) ; 
 int AC97_STEREO_MUTES ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_valid_reg (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write (struct snd_ac97*,int,unsigned short) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,unsigned short) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ac97*) ; 

__attribute__((used)) static int snd_ac97_cmute_new_stereo(struct snd_card *card, char *name, int reg,
				     int check_stereo, int check_amix,
				     struct snd_ac97 *ac97)
{
	struct snd_kcontrol *kctl;
	int err;
	unsigned short val, val1, mute_mask;

	if (! snd_ac97_valid_reg(ac97, reg))
		return 0;

	mute_mask = 0x8000;
	val = snd_ac97_read(ac97, reg);
	if (check_stereo || (ac97->flags & AC97_STEREO_MUTES)) {
		/* check whether both mute bits work */
		val1 = val | 0x8080;
		snd_ac97_write(ac97, reg, val1);
		if (val1 == snd_ac97_read(ac97, reg))
			mute_mask = 0x8080;
	}
	if (mute_mask == 0x8080) {
		struct snd_kcontrol_new tmp = AC97_DOUBLE(name, reg, 15, 7, 1, 1);
		if (check_amix)
			tmp.private_value |= (1 << 30);
		tmp.index = ac97->num;
		kctl = snd_ctl_new1(&tmp, ac97);
	} else {
		struct snd_kcontrol_new tmp = AC97_SINGLE(name, reg, 15, 1, 1);
		if (check_amix)
			tmp.private_value |= (1 << 30);
		tmp.index = ac97->num;
		kctl = snd_ctl_new1(&tmp, ac97);
	}
	err = snd_ctl_add(card, kctl);
	if (err < 0)
		return err;
	/* mute as default */
	snd_ac97_write_cache(ac97, reg, val | mute_mask);
	return 0;
}