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
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 unsigned int AC_AMPCAP_OFFSET_SHIFT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 unsigned int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void fix_volume_caps(struct hda_codec *codec, hda_nid_t dac)
{
	unsigned int caps;

	/* set the upper-limit for mixer amp to 0dB */
	caps = query_amp_caps(codec, dac, HDA_OUTPUT);
	caps &= ~(0x7f << AC_AMPCAP_NUM_STEPS_SHIFT);
	caps |= ((caps >> AC_AMPCAP_OFFSET_SHIFT) & 0x7f)
		<< AC_AMPCAP_NUM_STEPS_SHIFT;
	snd_hda_override_amp_caps(codec, dac, HDA_OUTPUT, caps);
}