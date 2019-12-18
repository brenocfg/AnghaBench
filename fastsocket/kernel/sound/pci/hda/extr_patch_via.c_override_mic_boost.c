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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_AMPCAP_MUTE_SHIFT ; 
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 int AC_AMPCAP_OFFSET_SHIFT ; 
 int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 int AC_WCAP_IN_AMP ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_override_wcaps (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void override_mic_boost(struct hda_codec *codec, hda_nid_t pin,
			       int offset, int num_steps, int step_size)
{
	snd_hda_override_wcaps(codec, pin,
			       get_wcaps(codec, pin) | AC_WCAP_IN_AMP);
	snd_hda_override_amp_caps(codec, pin, HDA_INPUT,
				  (offset << AC_AMPCAP_OFFSET_SHIFT) |
				  (num_steps << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (step_size << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));
}