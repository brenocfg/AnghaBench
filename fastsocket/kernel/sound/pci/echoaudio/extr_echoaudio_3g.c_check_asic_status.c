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
typedef  int u32 ;
struct echoaudio {int /*<<< orphan*/  asic_loaded; TYPE_1__* comm_page; int /*<<< orphan*/ * dsp_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_box_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  DSP_VC_TEST_ASIC ; 
 int E3G_ASIC_NOT_LOADED ; 
 int E3G_BOX_TYPE_MASK ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int check_asic_status(struct echoaudio *chip)
{
	u32 box_status;

	if (wait_handshake(chip))
		return -EIO;

	chip->comm_page->ext_box_status = cpu_to_le32(E3G_ASIC_NOT_LOADED);
	chip->asic_loaded = FALSE;
	clear_handshake(chip);
	send_vector(chip, DSP_VC_TEST_ASIC);

	if (wait_handshake(chip)) {
		chip->dsp_code = NULL;
		return -EIO;
	}

	box_status = le32_to_cpu(chip->comm_page->ext_box_status);
	DE_INIT(("box_status=%x\n", box_status));
	if (box_status == E3G_ASIC_NOT_LOADED)
		return -ENODEV;

	chip->asic_loaded = TRUE;
	return box_status & E3G_BOX_TYPE_MASK;
}