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
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  DSP_FNC_LOAD_LAYLA24_EXTERNAL_ASIC ; 
 int /*<<< orphan*/  DSP_FNC_LOAD_LAYLA24_PCI_CARD_ASIC ; 
 int FALSE ; 
 size_t FW_LAYLA24_1_ASIC ; 
 size_t FW_LAYLA24_2S_ASIC ; 
 int GML_48KHZ ; 
 int GML_CONVERTER_ENABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * card_fw ; 
 int check_asic_status (struct echoaudio*) ; 
 int load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int write_control_reg (struct echoaudio*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_asic(struct echoaudio *chip)
{
	int err;

	if (chip->asic_loaded)
		return 1;

	DE_INIT(("load_asic\n"));

	/* Give the DSP a few milliseconds to settle down */
	mdelay(10);

	/* Load the ASIC for the PCI card */
	err = load_asic_generic(chip, DSP_FNC_LOAD_LAYLA24_PCI_CARD_ASIC,
				&card_fw[FW_LAYLA24_1_ASIC]);
	if (err < 0)
		return err;

	chip->asic_code = &card_fw[FW_LAYLA24_2S_ASIC];

	/* Now give the new ASIC a little time to set up */
	mdelay(10);

	/* Do the external one */
	err = load_asic_generic(chip, DSP_FNC_LOAD_LAYLA24_EXTERNAL_ASIC,
				&card_fw[FW_LAYLA24_2S_ASIC]);
	if (err < 0)
		return FALSE;

	/* Now give the external ASIC a little time to set up */
	mdelay(10);

	/* See if it worked */
	err = check_asic_status(chip);

	/* Set up the control register if the load succeeded -
	   48 kHz, internal clock, S/PDIF RCA mode */
	if (!err)
		err = write_control_reg(chip, GML_CONVERTER_ENABLE | GML_48KHZ,
					TRUE);
	
	DE_INIT(("load_asic() done\n"));
	return err;
}