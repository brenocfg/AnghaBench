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
struct hda_jack_tbl {int jack_dirty; unsigned char action; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct hda_jack_tbl* snd_hda_jack_tbl_get_from_tag (struct hda_codec*,unsigned int) ; 

__attribute__((used)) static inline unsigned char
snd_hda_jack_get_action(struct hda_codec *codec, unsigned int tag)
{
	struct hda_jack_tbl *jack = snd_hda_jack_tbl_get_from_tag(codec, tag);
	if (jack) {
		jack->jack_dirty = 1;
		return jack->action;
	}
	return 0;
}