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
struct nid_path {int depth; int /*<<< orphan*/ * path; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_OUTPUT ; 
 scalar_t__ nid_has_volume (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hda_nid_t look_for_out_vol_nid(struct hda_codec *codec,
				      struct nid_path *path)
{
	int i;

	for (i = path->depth - 1; i >= 0; i--) {
		if (nid_has_volume(codec, path->path[i], HDA_OUTPUT))
			return path->path[i];
	}
	return 0;
}