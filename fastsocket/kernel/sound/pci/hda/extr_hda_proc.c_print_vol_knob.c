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
struct snd_info_buffer {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_VOL_KNB_CAP ; 
 int /*<<< orphan*/  AC_VERB_GET_VOLUME_KNOB_CONTROL ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void print_vol_knob(struct snd_info_buffer *buffer,
			   struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int cap = snd_hda_param_read(codec, nid,
					      AC_PAR_VOL_KNB_CAP);
	snd_iprintf(buffer, "  Volume-Knob: delta=%d, steps=%d, ",
		    (cap >> 7) & 1, cap & 0x7f);
	cap = snd_hda_codec_read(codec, nid, 0,
				 AC_VERB_GET_VOLUME_KNOB_CONTROL, 0);
	snd_iprintf(buffer, "direct=%d, val=%d\n",
		    (cap >> 7) & 1, cap & 0x7f);
}