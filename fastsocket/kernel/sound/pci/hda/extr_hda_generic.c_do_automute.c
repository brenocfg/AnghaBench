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
struct hda_gen_spec {unsigned long long mute_bits; scalar_t__ keep_vref_in_automute; scalar_t__ auto_mute_via_amp; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  unsigned long long hda_nid_t ;

/* Variables and functions */
 unsigned int PIN_HP ; 
 unsigned int PIN_IN ; 
 int /*<<< orphan*/  set_pin_eapd (struct hda_codec*,unsigned long long,int) ; 
 unsigned int snd_hda_codec_get_pin_target (struct hda_codec*,unsigned long long) ; 
 int /*<<< orphan*/  update_pin_ctl (struct hda_codec*,unsigned long long,unsigned int) ; 

__attribute__((used)) static void do_automute(struct hda_codec *codec, int num_pins, hda_nid_t *pins,
			bool mute)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	for (i = 0; i < num_pins; i++) {
		hda_nid_t nid = pins[i];
		unsigned int val, oldval;
		if (!nid)
			break;

		if (spec->auto_mute_via_amp) {
			if (mute)
				spec->mute_bits |= (1ULL << nid);
			else
				spec->mute_bits &= ~(1ULL << nid);
			set_pin_eapd(codec, nid, !mute);
			continue;
		}

		oldval = snd_hda_codec_get_pin_target(codec, nid);
		if (oldval & PIN_IN)
			continue; /* no mute for inputs */
		/* don't reset VREF value in case it's controlling
		 * the amp (see alc861_fixup_asus_amp_vref_0f())
		 */
		if (spec->keep_vref_in_automute)
			val = oldval & ~PIN_HP;
		else
			val = 0;
		if (!mute)
			val |= oldval;
		/* here we call update_pin_ctl() so that the pinctl is changed
		 * without changing the pinctl target value;
		 * the original target value will be still referred at the
		 * init / resume again
		 */
		update_pin_ctl(codec, nid, val);
		set_pin_eapd(codec, nid, !mute);
	}
}