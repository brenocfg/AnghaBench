#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ct_mixer {struct ct_atc* atc; } ;
struct ct_atc {int /*<<< orphan*/  (* spdif_in_unmute ) (struct ct_atc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* line_in_unmute ) (struct ct_atc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* spdif_out_unmute ) (struct ct_atc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* line_rear_unmute ) (struct ct_atc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* line_clfe_unmute ) (struct ct_atc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* line_surround_unmute ) (struct ct_atc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* line_front_unmute ) (struct ct_atc*,int) ;scalar_t__ (* have_digit_io_switch ) (struct ct_atc*) ;} ;
typedef  enum CTALSA_MIXER_CTL { ____Placeholder_CTALSA_MIXER_CTL } CTALSA_MIXER_CTL ;
struct TYPE_9__ {int /*<<< orphan*/  name; scalar_t__ ctl; } ;
struct TYPE_8__ {unsigned long private_value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t MIXER_DIGITAL_IO_S ; 
 int /*<<< orphan*/  MIXER_LINEIN_C_S ; 
 int /*<<< orphan*/  MIXER_LINEIN_P_S ; 
 int /*<<< orphan*/  MIXER_PCM_C_S ; 
 int /*<<< orphan*/  MIXER_SPDIFI_C_S ; 
 int /*<<< orphan*/  MIXER_SPDIFI_P_S ; 
 int /*<<< orphan*/  MIXER_SPDIFO_P_S ; 
 int /*<<< orphan*/  MIXER_WAVEC_P_S ; 
 int /*<<< orphan*/  MIXER_WAVEF_P_S ; 
 int /*<<< orphan*/  MIXER_WAVER_P_S ; 
 int /*<<< orphan*/  MIXER_WAVES_P_S ; 
 int SWH_MIXER_END ; 
 int SWH_MIXER_START ; 
 int VOL_MIXER_END ; 
 int VOL_MIXER_START ; 
 TYPE_7__* ct_kcontrol_init_table ; 
 int ct_mixer_kcontrol_new (struct ct_mixer*,TYPE_1__*) ; 
 TYPE_1__ iec958_ctl ; 
 TYPE_1__ iec958_default_ctl ; 
 TYPE_1__ iec958_mask_ctl ; 
 int /*<<< orphan*/  set_switch_state (struct ct_mixer*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct ct_atc*) ; 
 int /*<<< orphan*/  stub2 (struct ct_atc*,int) ; 
 int /*<<< orphan*/  stub3 (struct ct_atc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ct_atc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ct_atc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ct_atc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ct_atc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct ct_atc*,int /*<<< orphan*/ ) ; 
 TYPE_1__ swh_ctl ; 
 TYPE_1__ vol_ctl ; 

__attribute__((used)) static int ct_mixer_kcontrols_create(struct ct_mixer *mixer)
{
	enum CTALSA_MIXER_CTL type;
	struct ct_atc *atc = mixer->atc;
	int err;

	/* Create snd kcontrol instances on demand */
	for (type = VOL_MIXER_START; type <= VOL_MIXER_END; type++) {
		if (ct_kcontrol_init_table[type].ctl) {
			vol_ctl.name = ct_kcontrol_init_table[type].name;
			vol_ctl.private_value = (unsigned long)type;
			err = ct_mixer_kcontrol_new(mixer, &vol_ctl);
			if (err)
				return err;
		}
	}

	ct_kcontrol_init_table[MIXER_DIGITAL_IO_S].ctl =
					atc->have_digit_io_switch(atc);
	for (type = SWH_MIXER_START; type <= SWH_MIXER_END; type++) {
		if (ct_kcontrol_init_table[type].ctl) {
			swh_ctl.name = ct_kcontrol_init_table[type].name;
			swh_ctl.private_value = (unsigned long)type;
			err = ct_mixer_kcontrol_new(mixer, &swh_ctl);
			if (err)
				return err;
		}
	}

	err = ct_mixer_kcontrol_new(mixer, &iec958_mask_ctl);
	if (err)
		return err;

	err = ct_mixer_kcontrol_new(mixer, &iec958_default_ctl);
	if (err)
		return err;

	err = ct_mixer_kcontrol_new(mixer, &iec958_ctl);
	if (err)
		return err;

	atc->line_front_unmute(atc, 1);
	set_switch_state(mixer, MIXER_WAVEF_P_S, 1);
	atc->line_surround_unmute(atc, 0);
	set_switch_state(mixer, MIXER_WAVES_P_S, 0);
	atc->line_clfe_unmute(atc, 0);
	set_switch_state(mixer, MIXER_WAVEC_P_S, 0);
	atc->line_rear_unmute(atc, 0);
	set_switch_state(mixer, MIXER_WAVER_P_S, 0);
	atc->spdif_out_unmute(atc, 0);
	set_switch_state(mixer, MIXER_SPDIFO_P_S, 0);
	atc->line_in_unmute(atc, 0);
	set_switch_state(mixer, MIXER_LINEIN_P_S, 0);
	atc->spdif_in_unmute(atc, 0);
	set_switch_state(mixer, MIXER_SPDIFI_P_S, 0);

	set_switch_state(mixer, MIXER_PCM_C_S, 1);
	set_switch_state(mixer, MIXER_LINEIN_C_S, 1);
	set_switch_state(mixer, MIXER_SPDIFI_C_S, 1);

	return 0;
}