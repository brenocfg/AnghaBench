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
struct hda_codec {unsigned int (* power_filter ) (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ;int num_nodes; int /*<<< orphan*/  start_nid; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 unsigned int AC_WCAP_POWER ; 
 unsigned int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_check_power_state (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int stub1 (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sync_power_up_states(struct hda_codec *codec)
{
	hda_nid_t nid = codec->start_nid;
	int i;

	/* don't care if no filter is used */
	if (!codec->power_filter)
		return;

	for (i = 0; i < codec->num_nodes; i++, nid++) {
		unsigned int wcaps = get_wcaps(codec, nid);
		unsigned int target;
		if (!(wcaps & AC_WCAP_POWER))
			continue;
		target = codec->power_filter(codec, nid, AC_PWRST_D0);
		if (target == AC_PWRST_D0)
			continue;
		if (!snd_hda_check_power_state(codec, nid, target))
			snd_hda_codec_write(codec, nid, 0,
					    AC_VERB_SET_POWER_STATE, target);
	}
}