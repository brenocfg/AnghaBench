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
 int /*<<< orphan*/  cxt5066_analog_mic_boost ; 
 int snd_hda_input_mux_info (int /*<<< orphan*/ *,struct snd_ctl_elem_info*) ; 

__attribute__((used)) static int cxt5066_mic_boost_mux_enum_info(struct snd_kcontrol *kcontrol,
					   struct snd_ctl_elem_info *uinfo)
{
	return snd_hda_input_mux_info(&cxt5066_analog_mic_boost, uinfo);
}