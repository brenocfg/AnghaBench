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
struct snd_ac97 {int ext_id; scalar_t__ id; } ;

/* Variables and functions */
 int AC97_EI_SPDIF ; 
 scalar_t__ AC97_ID_ALC650F ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_scale_5bit_3db_max ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tlv (struct snd_ac97*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_controls_alc650 ; 
 int /*<<< orphan*/  snd_ac97_spdif_controls_alc650 ; 

__attribute__((used)) static int patch_alc650_specific(struct snd_ac97 * ac97)
{
	int err;

	if ((err = patch_build_controls(ac97, snd_ac97_controls_alc650, ARRAY_SIZE(snd_ac97_controls_alc650))) < 0)
		return err;
	if (ac97->ext_id & AC97_EI_SPDIF) {
		if ((err = patch_build_controls(ac97, snd_ac97_spdif_controls_alc650, ARRAY_SIZE(snd_ac97_spdif_controls_alc650))) < 0)
			return err;
	}
	if (ac97->id != AC97_ID_ALC650F)
		reset_tlv(ac97, "Master Playback Volume",
			  db_scale_5bit_3db_max);
	return 0;
}