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
struct hda_cvt_setup {scalar_t__ active; } ;
struct hda_codec {scalar_t__ no_sticky_stream; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 struct hda_cvt_setup* get_hda_cvt_setup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  really_cleanup_stream (struct hda_codec*,struct hda_cvt_setup*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ) ; 

void __snd_hda_codec_cleanup_stream(struct hda_codec *codec, hda_nid_t nid,
				    int do_now)
{
	struct hda_cvt_setup *p;

	if (!nid)
		return;

	if (codec->no_sticky_stream)
		do_now = 1;

	snd_printdd("hda_codec_cleanup_stream: NID=0x%x\n", nid);
	p = get_hda_cvt_setup(codec, nid);
	if (p) {
		/* here we just clear the active flag when do_now isn't set;
		 * actual clean-ups will be done later in
		 * purify_inactive_streams() called from snd_hda_codec_prpapre()
		 */
		if (do_now)
			really_cleanup_stream(codec, p);
		else
			p->active = 0;
	}
}