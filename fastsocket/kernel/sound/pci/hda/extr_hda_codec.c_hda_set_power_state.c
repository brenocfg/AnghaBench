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
struct TYPE_2__ {int /*<<< orphan*/  (* set_power_state ) (struct hda_codec*,scalar_t__,unsigned int) ;} ;
struct hda_codec {TYPE_1__ patch_ops; scalar_t__ epss; scalar_t__ mfg; scalar_t__ afg; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_D3 ; 
 unsigned int AC_PWRST_ERROR ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int HDA_RW_NO_RESPONSE_FALLBACK ; 
 unsigned int hda_sync_power_state (struct hda_codec*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_read (struct hda_codec*,scalar_t__,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_set_power_to_all (struct hda_codec*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,scalar_t__,unsigned int) ; 

__attribute__((used)) static unsigned int hda_set_power_state(struct hda_codec *codec,
					unsigned int power_state)
{
	hda_nid_t fg = codec->afg ? codec->afg : codec->mfg;
	int count;
	unsigned int state;
	int flags = 0;

	/* this delay seems necessary to avoid click noise at power-down */
	if (power_state == AC_PWRST_D3) {
		/* transition time less than 10ms for power down */
		msleep(codec->epss ? 10 : 100);
		flags = HDA_RW_NO_RESPONSE_FALLBACK;
	}

	/* repeat power states setting at most 10 times*/
	for (count = 0; count < 10; count++) {
		if (codec->patch_ops.set_power_state)
			codec->patch_ops.set_power_state(codec, fg,
							 power_state);
		else {
			snd_hda_codec_read(codec, fg, flags,
					   AC_VERB_SET_POWER_STATE,
					   power_state);
			snd_hda_codec_set_power_to_all(codec, fg, power_state);
		}
		state = hda_sync_power_state(codec, fg, power_state);
		if (!(state & AC_PWRST_ERROR))
			break;
	}

	return state;
}