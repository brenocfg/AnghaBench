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
typedef  int /*<<< orphan*/  u32 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_HASH_PINCAP_KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_caps_hash (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pin_cap ; 

u32 snd_hda_query_pin_caps(struct hda_codec *codec, hda_nid_t nid)
{
	return query_caps_hash(codec, nid, 0, HDA_HASH_PINCAP_KEY(nid),
			       read_pin_cap);
}