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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int ext_mic_present; scalar_t__ dc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_PIN_SENSE ; 
 int /*<<< orphan*/  AC_VERB_SET_CONNECT_SEL ; 
 int /*<<< orphan*/  cxt5066_olpc_select_mic (struct hda_codec*) ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static void cxt5066_olpc_automic(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int present;

	if (spec->dc_enable) /* don't do presence detection in DC mode */
		return;

	present = snd_hda_codec_read(codec, 0x1a, 0,
				     AC_VERB_GET_PIN_SENSE, 0) & 0x80000000;
	if (present)
		snd_printdd("CXT5066: external microphone detected\n");
	else
		snd_printdd("CXT5066: external microphone absent\n");

	snd_hda_codec_write(codec, 0x17, 0, AC_VERB_SET_CONNECT_SEL,
		present ? 0 : 1);
	spec->ext_mic_present = !!present;

	cxt5066_olpc_select_mic(codec);
}