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
struct hda_input_mux {int num_items; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {scalar_t__* imux_pins; struct hda_input_mux input_mux; } ;
struct alc_spec {scalar_t__ inv_dmic_pin; TYPE_1__ gen; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_AMP_SET_INPUT ; 
 int AC_AMP_SET_OUTPUT ; 
 int AC_AMP_SET_RIGHT ; 
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int HDA_OUTPUT ; 
 size_t NID_PATH_MUTE_CTL ; 
 int /*<<< orphan*/  get_adc_nid (struct hda_codec*,int,int) ; 
 int get_amp_direction_ (unsigned int) ; 
 int /*<<< orphan*/  get_amp_nid_ (unsigned int) ; 
 unsigned int snd_hda_codec_amp_read (struct hda_codec*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_flush_cache (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nid_path* snd_hda_get_nid_path (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_inv_dmic_sync_adc(struct hda_codec *codec, int adc_idx)
{
	struct alc_spec *spec = codec->spec;
	struct hda_input_mux *imux = &spec->gen.input_mux;
	struct nid_path *path;
	hda_nid_t nid;
	int i, dir, parm;
	unsigned int val;

	for (i = 0; i < imux->num_items; i++) {
		if (spec->gen.imux_pins[i] == spec->inv_dmic_pin)
			break;
	}
	if (i >= imux->num_items)
		return;

	path = snd_hda_get_nid_path(codec, spec->inv_dmic_pin,
				    get_adc_nid(codec, adc_idx, i));
	val = path->ctls[NID_PATH_MUTE_CTL];
	if (!val)
		return;
	nid = get_amp_nid_(val);
	dir = get_amp_direction_(val);
	parm = AC_AMP_SET_RIGHT |
		(dir == HDA_OUTPUT ? AC_AMP_SET_OUTPUT : AC_AMP_SET_INPUT);

	/* flush all cached amps at first */
	snd_hda_codec_flush_cache(codec);

	/* we care only right channel */
	val = snd_hda_codec_amp_read(codec, nid, 1, dir, 0);
	if (val & 0x80) /* if already muted, we don't need to touch */
		return;
	val |= 0x80;
	snd_hda_codec_write(codec, nid, 0, AC_VERB_SET_AMP_GAIN_MUTE,
			    parm | val);
}