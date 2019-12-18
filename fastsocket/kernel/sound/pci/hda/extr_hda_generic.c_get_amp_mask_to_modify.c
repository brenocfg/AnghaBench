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
 unsigned int AC_AMPCAP_MUTE ; 
 unsigned int AC_AMPCAP_NUM_STEPS ; 
 int /*<<< orphan*/  NID_PATH_BOOST_CTL ; 
 int /*<<< orphan*/  NID_PATH_MUTE_CTL ; 
 int /*<<< orphan*/  NID_PATH_VOL_CTL ; 
 scalar_t__ is_ctl_associated (struct hda_codec*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_amp_mask_to_modify(struct hda_codec *codec,
					   hda_nid_t nid, int dir, int idx,
					   unsigned int caps)
{
	unsigned int mask = 0xff;

	if (caps & AC_AMPCAP_MUTE) {
		if (is_ctl_associated(codec, nid, dir, idx, NID_PATH_MUTE_CTL))
			mask &= ~0x80;
	}
	if (caps & AC_AMPCAP_NUM_STEPS) {
		if (is_ctl_associated(codec, nid, dir, idx, NID_PATH_VOL_CTL) ||
		    is_ctl_associated(codec, nid, dir, idx, NID_PATH_BOOST_CTL))
			mask &= ~0x7f;
	}
	return mask;
}