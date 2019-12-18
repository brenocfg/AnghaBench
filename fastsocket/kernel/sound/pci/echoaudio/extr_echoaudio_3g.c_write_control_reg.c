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
typedef  scalar_t__ u32 ;
struct echoaudio {TYPE_1__* comm_page; } ;
struct TYPE_2__ {scalar_t__ control_register; scalar_t__ e3g_frq_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DSP_VC_WRITE_CONTROL_REG ; 
 int EIO ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int write_control_reg(struct echoaudio *chip, u32 ctl, u32 frq,
			     char force)
{
	if (wait_handshake(chip))
		return -EIO;

	DE_ACT(("WriteControlReg: Setting 0x%x, 0x%x\n", ctl, frq));

	ctl = cpu_to_le32(ctl);
	frq = cpu_to_le32(frq);

	if (ctl != chip->comm_page->control_register ||
	    frq != chip->comm_page->e3g_frq_register || force) {
		chip->comm_page->e3g_frq_register = frq;
		chip->comm_page->control_register = ctl;
		clear_handshake(chip);
		return send_vector(chip, DSP_VC_WRITE_CONTROL_REG);
	}

	DE_ACT(("WriteControlReg: not written, no change\n"));
	return 0;
}