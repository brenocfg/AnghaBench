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

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_CONNECT_SEL ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned int) ; 

__attribute__((used)) static void cxt5066_asus_automic(struct hda_codec *codec)
{
	unsigned int present;

	present = snd_hda_jack_detect(codec, 0x1b);
	snd_printdd("CXT5066: external microphone present=%d\n", present);
	snd_hda_codec_write(codec, 0x17, 0, AC_VERB_SET_CONNECT_SEL,
			    present ? 1 : 0);
}