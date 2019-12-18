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
struct nid_path {unsigned int* ctls; } ;
struct TYPE_2__ {int used; } ;
struct hda_gen_spec {TYPE_1__ paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 unsigned int AMP_VAL_COMPARE_MASK ; 
 struct nid_path* snd_array_elem (TYPE_1__*,int) ; 

__attribute__((used)) static bool is_ctl_used(struct hda_codec *codec, unsigned int val, int type)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	val &= AMP_VAL_COMPARE_MASK;
	for (i = 0; i < spec->paths.used; i++) {
		struct nid_path *path = snd_array_elem(&spec->paths, i);
		if ((path->ctls[type] & AMP_VAL_COMPARE_MASK) == val)
			return true;
	}
	return false;
}