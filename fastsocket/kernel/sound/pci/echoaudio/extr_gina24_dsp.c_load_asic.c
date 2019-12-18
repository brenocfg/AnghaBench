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
typedef  int u32 ;
struct firmware {int dummy; } ;
struct echoaudio {scalar_t__ device_id; struct firmware const* asic_code; scalar_t__ asic_loaded; } ;

/* Variables and functions */
 scalar_t__ DEVICE_ID_56361 ; 
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  DSP_FNC_LOAD_GINA24_ASIC ; 
 size_t FW_GINA24_301_ASIC ; 
 size_t FW_GINA24_361_ASIC ; 
 int GML_48KHZ ; 
 int GML_CONVERTER_ENABLE ; 
 int /*<<< orphan*/  TRUE ; 
 struct firmware* card_fw ; 
 int check_asic_status (struct echoaudio*) ; 
 int load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,struct firmware const*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int write_control_reg (struct echoaudio*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_asic(struct echoaudio *chip)
{
	u32 control_reg;
	int err;
	const struct firmware *fw;

	if (chip->asic_loaded)
		return 1;

	/* Give the DSP a few milliseconds to settle down */
	mdelay(10);

	/* Pick the correct ASIC for '301 or '361 Gina24 */
	if (chip->device_id == DEVICE_ID_56361)
		fw = &card_fw[FW_GINA24_361_ASIC];
	else
		fw = &card_fw[FW_GINA24_301_ASIC];

	if ((err = load_asic_generic(chip, DSP_FNC_LOAD_GINA24_ASIC, fw)) < 0)
		return err;

	chip->asic_code = fw;

	/* Now give the new ASIC a little time to set up */
	mdelay(10);
	/* See if it worked */
	err = check_asic_status(chip);

	/* Set up the control register if the load succeeded -
	   48 kHz, internal clock, S/PDIF RCA mode */
	if (!err) {
		control_reg = GML_CONVERTER_ENABLE | GML_48KHZ;
		err = write_control_reg(chip, control_reg, TRUE);
	}
	DE_INIT(("load_asic() done\n"));
	return err;
}