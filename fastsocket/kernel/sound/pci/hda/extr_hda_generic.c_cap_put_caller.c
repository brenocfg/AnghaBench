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
struct TYPE_2__ {int index; } ;
struct snd_kcontrol {scalar_t__ private_value; TYPE_1__ id; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct nid_path {scalar_t__* ctls; } ;
struct hda_input_mux {int num_items; } ;
struct hda_gen_spec {int /*<<< orphan*/  (* cap_sync_hook ) (struct hda_codec*,struct snd_ctl_elem_value*) ;struct hda_input_mux input_mux; } ;
struct hda_codec {int cached_write; int /*<<< orphan*/  control_mutex; struct hda_gen_spec* spec; } ;
typedef  int (* put_call_t ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;

/* Variables and functions */
 struct nid_path* get_input_path (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_codec_flush_cache (struct hda_codec*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int cap_put_caller(struct snd_kcontrol *kcontrol,
			  struct snd_ctl_elem_value *ucontrol,
			  put_call_t func, int type)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;
	const struct hda_input_mux *imux;
	struct nid_path *path;
	int i, adc_idx, err = 0;

	imux = &spec->input_mux;
	adc_idx = kcontrol->id.index;
	mutex_lock(&codec->control_mutex);
	/* we use the cache-only update at first since multiple input paths
	 * may shared the same amp; by updating only caches, the redundant
	 * writes to hardware can be reduced.
	 */
	codec->cached_write = 1;
	for (i = 0; i < imux->num_items; i++) {
		path = get_input_path(codec, adc_idx, i);
		if (!path || !path->ctls[type])
			continue;
		kcontrol->private_value = path->ctls[type];
		err = func(kcontrol, ucontrol);
		if (err < 0)
			goto error;
	}
 error:
	codec->cached_write = 0;
	mutex_unlock(&codec->control_mutex);
	snd_hda_codec_flush_cache(codec); /* flush the updates */
	if (err >= 0 && spec->cap_sync_hook)
		spec->cap_sync_hook(codec, ucontrol);
	return err;
}