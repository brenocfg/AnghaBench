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
struct snd_kcontrol_new {int index; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int used; } ;
struct hda_gen_spec {TYPE_1__ kctls; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 struct snd_kcontrol_new* snd_array_elem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool find_kctl_name(struct hda_codec *codec, const char *name, int idx)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	for (i = 0; i < spec->kctls.used; i++) {
		struct snd_kcontrol_new *kctl = snd_array_elem(&spec->kctls, i);
		if (!strcmp(kctl->name, name) && kctl->index == idx)
			return true;
	}
	return false;
}