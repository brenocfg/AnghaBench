#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nid_path {int depth; scalar_t__* path; } ;
struct TYPE_2__ {int used; } ;
struct hda_gen_spec {TYPE_1__ paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ is_nid_contained (struct nid_path*,int) ; 
 struct nid_path* snd_array_elem (TYPE_1__*,int) ; 

__attribute__((used)) static struct nid_path *get_nid_path(struct hda_codec *codec,
				     hda_nid_t from_nid, hda_nid_t to_nid,
				     int anchor_nid)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	for (i = 0; i < spec->paths.used; i++) {
		struct nid_path *path = snd_array_elem(&spec->paths, i);
		if (path->depth <= 0)
			continue;
		if ((!from_nid || path->path[0] == from_nid) &&
		    (!to_nid || path->path[path->depth - 1] == to_nid)) {
			if (!anchor_nid ||
			    (anchor_nid > 0 && is_nid_contained(path, anchor_nid)) ||
			    (anchor_nid < 0 && !is_nid_contained(path, anchor_nid)))
				return path;
		}
	}
	return NULL;
}