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
struct hda_codec {int vendor_id; } ;

/* Variables and functions */
 int alc_read_coef_idx (struct hda_codec*,int) ; 
 int /*<<< orphan*/  alc_write_coef_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static void alc_headset_mode_unplugged(struct hda_codec *codec)
{
	int val;

	switch (codec->vendor_id) {
	case 0x10ec0283:
		alc_write_coef_idx(codec, 0x1b, 0x0c0b);
		alc_write_coef_idx(codec, 0x45, 0xc429);
		val = alc_read_coef_idx(codec, 0x35);
		alc_write_coef_idx(codec, 0x35, val & 0xbfff);
		alc_write_coef_idx(codec, 0x06, 0x2104);
		alc_write_coef_idx(codec, 0x1a, 0x0001);
		alc_write_coef_idx(codec, 0x26, 0x0004);
		alc_write_coef_idx(codec, 0x32, 0x42a3);
		break;
	case 0x10ec0292:
		alc_write_coef_idx(codec, 0x76, 0x000e);
		alc_write_coef_idx(codec, 0x6c, 0x2400);
		alc_write_coef_idx(codec, 0x18, 0x7308);
		alc_write_coef_idx(codec, 0x6b, 0xc429);
		break;
	case 0x10ec0668:
		alc_write_coef_idx(codec, 0x15, 0x0d40);
		alc_write_coef_idx(codec, 0xb7, 0x802b);
		break;
	}
	snd_printdd("Headset jack set to unplugged mode.\n");
}