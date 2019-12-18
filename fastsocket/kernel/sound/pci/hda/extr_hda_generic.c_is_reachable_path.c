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
 scalar_t__ snd_hda_get_conn_index (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool is_reachable_path(struct hda_codec *codec,
			      hda_nid_t from_nid, hda_nid_t to_nid)
{
	if (!from_nid || !to_nid)
		return false;
	return snd_hda_get_conn_index(codec, to_nid, from_nid, true) >= 0;
}