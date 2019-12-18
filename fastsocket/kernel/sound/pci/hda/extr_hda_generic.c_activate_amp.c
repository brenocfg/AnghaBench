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
 unsigned int get_amp_mask_to_modify (struct hda_codec*,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 unsigned int get_amp_val_to_activate (struct hda_codec*,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 scalar_t__ is_active_nid (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 
 unsigned int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_codec_amp_stereo (struct hda_codec*,int /*<<< orphan*/ ,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void activate_amp(struct hda_codec *codec, hda_nid_t nid, int dir,
			 int idx, int idx_to_check, bool enable)
{
	unsigned int caps;
	unsigned int mask, val;

	if (!enable && is_active_nid(codec, nid, dir, idx_to_check))
		return;

	caps = query_amp_caps(codec, nid, dir);
	val = get_amp_val_to_activate(codec, nid, dir, caps, enable);
	mask = get_amp_mask_to_modify(codec, nid, dir, idx_to_check, caps);
	if (!mask)
		return;

	val &= mask;
	snd_hda_codec_amp_stereo(codec, nid, dir, idx, mask, val);
}