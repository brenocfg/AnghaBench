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
struct hda_jack_tbl {int jack_detect; unsigned char action; int tag; scalar_t__ callback; } ;
struct hda_codec {scalar_t__ jackpoll_interval; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
typedef  scalar_t__ hda_jack_callback ;

/* Variables and functions */
 int AC_USRSP_EN ; 
 int /*<<< orphan*/  AC_VERB_SET_UNSOLICITED_ENABLE ; 
 int ENOMEM ; 
 int snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_new (struct hda_codec*,int /*<<< orphan*/ ) ; 

int snd_hda_jack_detect_enable_callback(struct hda_codec *codec, hda_nid_t nid,
					unsigned char action,
					hda_jack_callback cb)
{
	struct hda_jack_tbl *jack = snd_hda_jack_tbl_new(codec, nid);
	if (!jack)
		return -ENOMEM;
	if (jack->jack_detect)
		return 0; /* already registered */
	jack->jack_detect = 1;
	if (action)
		jack->action = action;
	if (cb)
		jack->callback = cb;
	if (codec->jackpoll_interval > 0)
		return 0; /* No unsol if we're polling instead */
	return snd_hda_codec_write_cache(codec, nid, 0,
					 AC_VERB_SET_UNSOLICITED_ENABLE,
					 AC_USRSP_EN | jack->tag);
}