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
struct hda_verb {int member_0; int member_2; int /*<<< orphan*/  member_1; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_CONNECT_SEL ; 
 int AMP_OUT_UNMUTE ; 
 int /*<<< orphan*/  cxt5066_olpc_select_mic (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,struct hda_verb const*) ; 

__attribute__((used)) static void cxt5066_enable_dc(struct hda_codec *codec)
{
	const struct hda_verb enable_dc_mode[] = {
		/* disable gain */
		{0x17, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE},

		/* switch to DC input */
		{0x17, AC_VERB_SET_CONNECT_SEL, 3},
		{}
	};

	/* configure as input source */
	snd_hda_sequence_write(codec, enable_dc_mode);
	cxt5066_olpc_select_mic(codec); /* also sets configured bias */
}