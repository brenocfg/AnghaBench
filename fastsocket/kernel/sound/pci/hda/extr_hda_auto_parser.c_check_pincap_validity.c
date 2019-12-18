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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
#define  AC_JACK_DIG_OTHER_OUT 132 
#define  AC_JACK_HP_OUT 131 
#define  AC_JACK_LINE_OUT 130 
#define  AC_JACK_SPDIF_OUT 129 
#define  AC_JACK_SPEAKER 128 
 unsigned int AC_PINCAP_IN ; 
 unsigned int AC_PINCAP_OUT ; 
 unsigned int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_pincap_validity(struct hda_codec *codec, hda_nid_t pin,
				  unsigned int dev)
{
	unsigned int pincap = snd_hda_query_pin_caps(codec, pin);

	/* some old hardware don't return the proper pincaps */
	if (!pincap)
		return true;

	switch (dev) {
	case AC_JACK_LINE_OUT:
	case AC_JACK_SPEAKER:
	case AC_JACK_HP_OUT:
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHER_OUT:
		return !!(pincap & AC_PINCAP_OUT);
	default:
		return !!(pincap & AC_PINCAP_IN);
	}
}