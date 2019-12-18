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
struct snd_card {int dummy; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_volume_resolution (struct snd_ac97*,int,unsigned char*,unsigned char*) ; 
 int snd_ac97_cmute_new_stereo (struct snd_card*,char*,int,int,int,struct snd_ac97*) ; 
 int snd_ac97_cvol_new (struct snd_card*,char*,int,unsigned char,unsigned char,struct snd_ac97*) ; 
 scalar_t__ snd_ac97_try_bit (struct snd_ac97*,int,int) ; 
 int /*<<< orphan*/  snd_ac97_valid_reg (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static int snd_ac97_cmix_new_stereo(struct snd_card *card, const char *pfx,
				    int reg, int check_stereo, int check_amix,
				    struct snd_ac97 *ac97)
{
	int err;
	char name[44];
	unsigned char lo_max, hi_max;

	if (! snd_ac97_valid_reg(ac97, reg))
		return 0;

	if (snd_ac97_try_bit(ac97, reg, 15)) {
		sprintf(name, "%s Switch", pfx);
		if ((err = snd_ac97_cmute_new_stereo(card, name, reg,
						     check_stereo, check_amix,
						     ac97)) < 0)
			return err;
	}
	check_volume_resolution(ac97, reg, &lo_max, &hi_max);
	if (lo_max) {
		sprintf(name, "%s Volume", pfx);
		if ((err = snd_ac97_cvol_new(card, name, reg, lo_max, hi_max, ac97)) < 0)
			return err;
	}
	return 0;
}