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
typedef  int u16 ;
struct echoaudio {int device_id; int subdevice_id; int input_clock_types; int digital_modes; void* bad_board; void* digital_in_automute; void* professional_spdif; int /*<<< orphan*/  digital_mode; int /*<<< orphan*/ * dsp_code_to_load; } ;

/* Variables and functions */
 scalar_t__ DEVICE_ID_56361 ; 
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  DIGITAL_MODE_SPDIF_RCA ; 
 int ECHOCAPS_HAS_DIGITAL_MODE_ADAT ; 
 int ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_OPTICAL ; 
 int ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_RCA ; 
 int ECHO_CLOCK_BIT_ADAT ; 
 int ECHO_CLOCK_BIT_INTERNAL ; 
 int ECHO_CLOCK_BIT_SPDIF ; 
 int ECHO_CLOCK_BIT_WORD ; 
 int ENODEV ; 
 void* FALSE ; 
 size_t FW_MONA_301_DSP ; 
 size_t FW_MONA_361_DSP ; 
 int MONA ; 
 void* TRUE ; 
 int /*<<< orphan*/ * card_fw ; 
 int init_dsp_comm_page (struct echoaudio*) ; 
 int init_line_levels (struct echoaudio*) ; 
 int load_firmware (struct echoaudio*) ; 
 int set_digital_mode (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int set_professional_spdif (struct echoaudio*,void*) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int init_hw(struct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int err;

	DE_INIT(("init_hw() - Mona\n"));
	if (snd_BUG_ON((subdevice_id & 0xfff0) != MONA))
		return -ENODEV;

	if ((err = init_dsp_comm_page(chip))) {
		DE_INIT(("init_hw - could not initialize DSP comm page\n"));
		return err;
	}

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = TRUE;
	chip->input_clock_types =
		ECHO_CLOCK_BIT_INTERNAL | ECHO_CLOCK_BIT_SPDIF |
		ECHO_CLOCK_BIT_WORD | ECHO_CLOCK_BIT_ADAT;
	chip->digital_modes =
		ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_RCA |
		ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_OPTICAL |
		ECHOCAPS_HAS_DIGITAL_MODE_ADAT;

	/* Mona comes in both '301 and '361 flavors */
	if (chip->device_id == DEVICE_ID_56361)
		chip->dsp_code_to_load = &card_fw[FW_MONA_361_DSP];
	else
		chip->dsp_code_to_load = &card_fw[FW_MONA_301_DSP];

	chip->digital_mode = DIGITAL_MODE_SPDIF_RCA;
	chip->professional_spdif = FALSE;
	chip->digital_in_automute = TRUE;

	if ((err = load_firmware(chip)) < 0)
		return err;
	chip->bad_board = FALSE;

	if ((err = init_line_levels(chip)) < 0)
		return err;

	err = set_digital_mode(chip, DIGITAL_MODE_SPDIF_RCA);
	if (err < 0)
		return err;
	err = set_professional_spdif(chip, TRUE);

	DE_INIT(("init_hw done\n"));
	return err;
}