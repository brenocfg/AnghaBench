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
 int get_amp_val_to_activate (struct hda_codec*,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 unsigned int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_codec_amp_init_stereo (struct hda_codec*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void init_amp(struct hda_codec *codec, hda_nid_t nid, int dir, int idx)
{
	unsigned int caps = query_amp_caps(codec, nid, dir);
	int val = get_amp_val_to_activate(codec, nid, dir, caps, false);
	snd_hda_codec_amp_init_stereo(codec, nid, dir, idx, 0xff, val);
}