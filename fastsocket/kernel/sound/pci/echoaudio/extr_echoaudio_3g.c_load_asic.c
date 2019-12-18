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
struct echoaudio {int /*<<< orphan*/ * asic_code; scalar_t__ asic_loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_FNC_LOAD_3G_ASIC ; 
 int /*<<< orphan*/  E3G_48KHZ ; 
 int /*<<< orphan*/  E3G_FREQ_REG_DEFAULT ; 
 size_t FW_3G_ASIC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * card_fw ; 
 int check_asic_status (struct echoaudio*) ; 
 int load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int write_control_reg (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_asic(struct echoaudio *chip)
{
	int box_type, err;

	if (chip->asic_loaded)
		return 0;

	/* Give the DSP a few milliseconds to settle down */
	mdelay(2);

	err = load_asic_generic(chip, DSP_FNC_LOAD_3G_ASIC,
				&card_fw[FW_3G_ASIC]);
	if (err < 0)
		return err;

	chip->asic_code = &card_fw[FW_3G_ASIC];

	/* Now give the new ASIC some time to set up */
	msleep(1000);
	/* See if it worked */
	box_type = check_asic_status(chip);

	/* Set up the control register if the load succeeded -
	 * 48 kHz, internal clock, S/PDIF RCA mode */
	if (box_type >= 0) {
		err = write_control_reg(chip, E3G_48KHZ,
					E3G_FREQ_REG_DEFAULT, TRUE);
		if (err < 0)
			return err;
	}

	return box_type;
}