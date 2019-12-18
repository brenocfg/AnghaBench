#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lo_as_master; } ;
struct TYPE_4__ {TYPE_1__ ad18xx; } ;
struct snd_ac97 {TYPE_2__ spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_ad1888_controls ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 

__attribute__((used)) static int patch_ad1888_specific(struct snd_ac97 *ac97)
{
	if (!ac97->spec.ad18xx.lo_as_master) {
		/* rename 0x04 as "Master" and 0x02 as "Master Surround" */
		snd_ac97_rename_vol_ctl(ac97, "Master Playback",
					"Master Surround Playback");
		snd_ac97_rename_vol_ctl(ac97, "Headphone Playback",
					"Master Playback");
	}
	return patch_build_controls(ac97, snd_ac97_ad1888_controls, ARRAY_SIZE(snd_ac97_ad1888_controls));
}