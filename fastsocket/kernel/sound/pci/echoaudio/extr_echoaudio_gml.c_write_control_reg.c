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
typedef  int /*<<< orphan*/  u32 ;
struct echoaudio {TYPE_1__* comm_page; scalar_t__ digital_in_automute; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DSP_VC_WRITE_CONTROL_REG ; 
 int EIO ; 
 int /*<<< orphan*/  GML_DIGITAL_IN_AUTO_MUTE ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int write_control_reg(struct echoaudio *chip, u32 value, char force)
{
	/* Handle the digital input auto-mute */
	if (chip->digital_in_automute)
		value |= GML_DIGITAL_IN_AUTO_MUTE;
	else
		value &= ~GML_DIGITAL_IN_AUTO_MUTE;

	DE_ACT(("write_control_reg: 0x%x\n", value));

	/* Write the control register */
	value = cpu_to_le32(value);
	if (value != chip->comm_page->control_register || force) {
		if (wait_handshake(chip))
			return -EIO;
		chip->comm_page->control_register = value;
		clear_handshake(chip);
		return send_vector(chip, DSP_VC_WRITE_CONTROL_REG);
	}
	return 0;
}