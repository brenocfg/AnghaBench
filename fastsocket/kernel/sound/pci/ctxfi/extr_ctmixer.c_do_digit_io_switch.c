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
struct ct_mixer {int dummy; } ;
struct ct_atc {int /*<<< orphan*/  (* line_in_unmute ) (struct ct_atc*,int) ;int /*<<< orphan*/  (* spdif_in_unmute ) (struct ct_atc*,int) ;int /*<<< orphan*/  (* spdif_out_unmute ) (struct ct_atc*,scalar_t__) ;int /*<<< orphan*/  (* select_mic_in ) (struct ct_atc*) ;int /*<<< orphan*/  (* select_line_in ) (struct ct_atc*) ;int /*<<< orphan*/  (* select_digit_io ) (struct ct_atc*) ;struct ct_mixer* mixer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXER_LINEIN_C_S ; 
 int /*<<< orphan*/  MIXER_MIC_C_S ; 
 int /*<<< orphan*/  MIXER_SPDIFO_P_S ; 
 scalar_t__ get_switch_state (struct ct_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ct_atc*) ; 
 int /*<<< orphan*/  stub2 (struct ct_atc*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct ct_atc*,int) ; 
 int /*<<< orphan*/  stub4 (struct ct_atc*,int) ; 
 int /*<<< orphan*/  stub5 (struct ct_atc*) ; 
 int /*<<< orphan*/  stub6 (struct ct_atc*) ; 
 int /*<<< orphan*/  stub7 (struct ct_atc*,scalar_t__) ; 
 int /*<<< orphan*/  stub8 (struct ct_atc*,int) ; 
 int /*<<< orphan*/  stub9 (struct ct_atc*,int) ; 

__attribute__((used)) static void
do_digit_io_switch(struct ct_atc *atc, int state)
{
	struct ct_mixer *mixer = atc->mixer;

	if (state) {
		atc->select_digit_io(atc);
		atc->spdif_out_unmute(atc,
				get_switch_state(mixer, MIXER_SPDIFO_P_S));
		atc->spdif_in_unmute(atc, 1);
		atc->line_in_unmute(atc, 0);
		return;
	}

	if (get_switch_state(mixer, MIXER_LINEIN_C_S))
		atc->select_line_in(atc);
	else if (get_switch_state(mixer, MIXER_MIC_C_S))
		atc->select_mic_in(atc);

	atc->spdif_out_unmute(atc, 0);
	atc->spdif_in_unmute(atc, 0);
	atc->line_in_unmute(atc, 1);
	return;
}