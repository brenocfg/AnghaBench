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
struct snd_kcontrol_new {int /*<<< orphan*/  index; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_card {int dummy; } ;
struct snd_ac97 {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 struct snd_kcontrol_new AC97_DOUBLE (char*,int,int,int /*<<< orphan*/ ,unsigned int,int) ; 
 int AC97_PCM ; 
 int AC97_PHONE ; 
 struct snd_kcontrol_new AC97_SINGLE (char*,int,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  db_scale_5bit_12db_max ; 
 int /*<<< orphan*/  find_db_scale (unsigned int) ; 
 int /*<<< orphan*/  set_tlv_db_scale (struct snd_kcontrol*,int /*<<< orphan*/ ) ; 
 int snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_valid_reg (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ac97*) ; 

__attribute__((used)) static int snd_ac97_cvol_new(struct snd_card *card, char *name, int reg, unsigned int lo_max,
			     unsigned int hi_max, struct snd_ac97 *ac97)
{
	int err;
	struct snd_kcontrol *kctl;

	if (! snd_ac97_valid_reg(ac97, reg))
		return 0;
	if (hi_max) {
		/* invert */
		struct snd_kcontrol_new tmp = AC97_DOUBLE(name, reg, 8, 0, lo_max, 1);
		tmp.index = ac97->num;
		kctl = snd_ctl_new1(&tmp, ac97);
	} else {
		/* invert */
		struct snd_kcontrol_new tmp = AC97_SINGLE(name, reg, 0, lo_max, 1);
		tmp.index = ac97->num;
		kctl = snd_ctl_new1(&tmp, ac97);
	}
	if (reg >= AC97_PHONE && reg <= AC97_PCM)
		set_tlv_db_scale(kctl, db_scale_5bit_12db_max);
	else
		set_tlv_db_scale(kctl, find_db_scale(lo_max));
	err = snd_ctl_add(card, kctl);
	if (err < 0)
		return err;
	snd_ac97_write_cache(ac97, reg,
			     (snd_ac97_read(ac97, reg) & 0x8080) |
			     lo_max | (hi_max << 8));
	return 0;
}