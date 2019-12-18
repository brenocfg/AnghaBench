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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_scale_6bit_6db_max ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_tlv (struct snd_ac97*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_controls_ad1885 ; 

__attribute__((used)) static int patch_ad1885_specific(struct snd_ac97 * ac97)
{
	int err;

	if ((err = patch_build_controls(ac97, snd_ac97_controls_ad1885, ARRAY_SIZE(snd_ac97_controls_ad1885))) < 0)
		return err;
	reset_tlv(ac97, "Headphone Playback Volume",
		  db_scale_6bit_6db_max);
	return 0;
}