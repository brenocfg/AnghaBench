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
 int /*<<< orphan*/  HDA_HASH_KEY (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int write_caps_hash (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

int snd_hda_override_amp_caps(struct hda_codec *codec, hda_nid_t nid, int dir,
			      unsigned int caps)
{
	return write_caps_hash(codec, HDA_HASH_KEY(nid, dir, 0), caps);
}