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
struct echoaudio {int sample_rate; TYPE_1__* comm_page; } ;
struct TYPE_2__ {void* control_register; void* sample_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DSP_VC_UPDATE_CLOCKS ; 
 int EINVAL ; 
 int EIO ; 
 int MIA_32000 ; 
 int MIA_44100 ; 
 int MIA_48000 ; 
 int MIA_88200 ; 
 int MIA_96000 ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 void* cpu_to_le32 (int) ; 
 int le32_to_cpu (void*) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int set_sample_rate(struct echoaudio *chip, u32 rate)
{
	u32 control_reg;

	switch (rate) {
	case 96000:
		control_reg = MIA_96000;
		break;
	case 88200:
		control_reg = MIA_88200;
		break;
	case 48000:
		control_reg = MIA_48000;
		break;
	case 44100:
		control_reg = MIA_44100;
		break;
	case 32000:
		control_reg = MIA_32000;
		break;
	default:
		DE_ACT(("set_sample_rate: %d invalid!\n", rate));
		return -EINVAL;
	}

	/* Set the control register if it has changed */
	if (control_reg != le32_to_cpu(chip->comm_page->control_register)) {
		if (wait_handshake(chip))
			return -EIO;

		chip->comm_page->sample_rate = cpu_to_le32(rate);	/* ignored by the DSP */
		chip->comm_page->control_register = cpu_to_le32(control_reg);
		chip->sample_rate = rate;

		clear_handshake(chip);
		return send_vector(chip, DSP_VC_UPDATE_CLOCKS);
	}
	return 0;
}