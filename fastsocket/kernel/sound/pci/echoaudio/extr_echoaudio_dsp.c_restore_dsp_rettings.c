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
struct echoaudio {int /*<<< orphan*/  output_clock; int /*<<< orphan*/  input_clock; scalar_t__ meters_enabled; int /*<<< orphan*/  sample_rate; TYPE_1__* comm_page; } ;
struct TYPE_2__ {int handshake; int /*<<< orphan*/  gd_spdif_status; int /*<<< orphan*/  gd_clock_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  DSP_VC_METERS_ON ; 
 int /*<<< orphan*/  DSP_VC_UPDATE_FLAGS ; 
 int EIO ; 
 int /*<<< orphan*/  GD_CLOCK_UNDEF ; 
 int /*<<< orphan*/  GD_SPDIF_STATUS_UNDEF ; 
 int check_asic_status (struct echoaudio*) ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_input_clock (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_output_clock (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int set_sample_rate (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ update_input_line_level (struct echoaudio*) ; 
 scalar_t__ update_output_line_level (struct echoaudio*) ; 
 scalar_t__ update_vmixer_level (struct echoaudio*) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int restore_dsp_rettings(struct echoaudio *chip)
{
	int err;
	DE_INIT(("restore_dsp_settings\n"));

	if ((err = check_asic_status(chip)) < 0)
		return err;

	/* @ Gina20/Darla20 only. Should be harmless for other cards. */
	chip->comm_page->gd_clock_state = GD_CLOCK_UNDEF;
	chip->comm_page->gd_spdif_status = GD_SPDIF_STATUS_UNDEF;
	chip->comm_page->handshake = 0xffffffff;

	if ((err = set_sample_rate(chip, chip->sample_rate)) < 0)
		return err;

	if (chip->meters_enabled)
		if (send_vector(chip, DSP_VC_METERS_ON) < 0)
			return -EIO;

#ifdef ECHOCARD_HAS_EXTERNAL_CLOCK
	if (set_input_clock(chip, chip->input_clock) < 0)
		return -EIO;
#endif

#ifdef ECHOCARD_HAS_OUTPUT_CLOCK_SWITCH
	if (set_output_clock(chip, chip->output_clock) < 0)
		return -EIO;
#endif

	if (update_output_line_level(chip) < 0)
		return -EIO;

	if (update_input_line_level(chip) < 0)
		return -EIO;

#ifdef ECHOCARD_HAS_VMIXER
	if (update_vmixer_level(chip) < 0)
		return -EIO;
#endif

	if (wait_handshake(chip) < 0)
		return -EIO;
	clear_handshake(chip);

	DE_INIT(("restore_dsp_rettings done\n"));
	return send_vector(chip, DSP_VC_UPDATE_FLAGS);
}