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
typedef  int u32 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_CONV ; 
 int /*<<< orphan*/  AC_VERB_GET_STREAM_FORMAT ; 
 int /*<<< orphan*/  AC_VERB_SET_CHANNEL_STREAMID ; 
 int /*<<< orphan*/  AC_VERB_SET_STREAM_FORMAT ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void ca0132_setup_stream(struct hda_codec *codec, hda_nid_t nid,
				 u32 stream_tag,
				 int channel_id, int format)
{
	unsigned int oldval, newval;

	if (!nid)
		return;

	snd_printdd(
		   "ca0132_setup_stream: NID=0x%x, stream=0x%x, "
		   "channel=%d, format=0x%x\n",
		   nid, stream_tag, channel_id, format);

	/* update the format-id if changed */
	oldval = snd_hda_codec_read(codec, nid, 0,
				    AC_VERB_GET_STREAM_FORMAT,
				    0);
	if (oldval != format) {
		msleep(20);
		snd_hda_codec_write(codec, nid, 0,
				    AC_VERB_SET_STREAM_FORMAT,
				    format);
	}

	oldval = snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_CONV, 0);
	newval = (stream_tag << 4) | channel_id;
	if (oldval != newval) {
		snd_hda_codec_write(codec, nid, 0,
				    AC_VERB_SET_CHANNEL_STREAMID,
				    newval);
	}
}