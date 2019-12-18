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
typedef  int hda_nid_t ;

/* Variables and functions */
 int AC_AMPCAP_MIN_MUTE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int query_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_cx5051_fake_mutes(struct hda_codec *codec)
{
	static hda_nid_t out_nids[] = {
		0x10, 0x11, 0
	};
	hda_nid_t *p;

	for (p = out_nids; *p; p++)
		snd_hda_override_amp_caps(codec, *p, HDA_OUTPUT,
					  AC_AMPCAP_MIN_MUTE |
					  query_amp_caps(codec, *p, HDA_OUTPUT));
}