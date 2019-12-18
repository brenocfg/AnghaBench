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
struct hda_jack_tbl {int jack_dirty; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 unsigned int AC_UNSOL_RES_TAG_SHIFT ; 
 int /*<<< orphan*/  call_jack_callback (struct hda_codec*,struct hda_jack_tbl*) ; 
 int /*<<< orphan*/  snd_hda_jack_report_sync (struct hda_codec*) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get_from_tag (struct hda_codec*,int) ; 

void snd_hda_jack_unsol_event(struct hda_codec *codec, unsigned int res)
{
	struct hda_jack_tbl *event;
	int tag = (res >> AC_UNSOL_RES_TAG_SHIFT) & 0x7f;

	event = snd_hda_jack_tbl_get_from_tag(codec, tag);
	if (!event)
		return;
	event->jack_dirty = 1;

	call_jack_callback(codec, event);
	snd_hda_jack_report_sync(codec);
}