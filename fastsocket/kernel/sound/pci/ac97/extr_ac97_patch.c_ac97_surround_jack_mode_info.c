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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int ac97_enum_text_info (struct snd_kcontrol*,struct snd_ctl_elem_info*,char const**,int) ; 

__attribute__((used)) static int ac97_surround_jack_mode_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	static const char *texts[] = { "Shared", "Independent" };
	return ac97_enum_text_info(kcontrol, uinfo, texts, 2);
}