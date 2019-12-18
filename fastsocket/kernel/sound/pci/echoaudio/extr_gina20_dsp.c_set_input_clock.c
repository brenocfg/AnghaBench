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
typedef  int u16 ;
struct echoaudio {int input_clock; void* clock_state; TYPE_1__* comm_page; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  spdif_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  gd_spdif_status; void* gd_clock_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DSP_VC_SET_GD_AUDIO_STATE ; 
#define  ECHO_CLOCK_INTERNAL 129 
#define  ECHO_CLOCK_SPDIF 128 
 int EINVAL ; 
 void* GD_CLOCK_SPDIFIN ; 
 void* GD_CLOCK_UNDEF ; 
 int /*<<< orphan*/  GD_SPDIF_STATUS_NOCHANGE ; 
 int /*<<< orphan*/  GD_SPDIF_STATUS_UNDEF ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sample_rate (struct echoaudio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_input_clock(struct echoaudio *chip, u16 clock)
{
	DE_ACT(("set_input_clock:\n"));

	switch (clock) {
	case ECHO_CLOCK_INTERNAL:
		/* Reset the audio state to unknown (just in case) */
		chip->clock_state = GD_CLOCK_UNDEF;
		chip->spdif_status = GD_SPDIF_STATUS_UNDEF;
		set_sample_rate(chip, chip->sample_rate);
		chip->input_clock = clock;
		DE_ACT(("Set Gina clock to INTERNAL\n"));
		break;
	case ECHO_CLOCK_SPDIF:
		chip->comm_page->gd_clock_state = GD_CLOCK_SPDIFIN;
		chip->comm_page->gd_spdif_status = GD_SPDIF_STATUS_NOCHANGE;
		clear_handshake(chip);
		send_vector(chip, DSP_VC_SET_GD_AUDIO_STATE);
		chip->clock_state = GD_CLOCK_SPDIFIN;
		DE_ACT(("Set Gina20 clock to SPDIF\n"));
		chip->input_clock = clock;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}