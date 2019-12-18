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
typedef  int u16 ;
struct echoaudio {int input_clock; int /*<<< orphan*/  digital_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  sample_rate; TYPE_1__* comm_page; int /*<<< orphan*/  opencount; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_clocks; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DIGITAL_MODE_ADAT ; 
 int EAGAIN ; 
#define  ECHO_CLOCK_ADAT 131 
#define  ECHO_CLOCK_INTERNAL 130 
#define  ECHO_CLOCK_SPDIF 129 
#define  ECHO_CLOCK_WORD 128 
 int EINVAL ; 
 int GML_ADAT_CLOCK ; 
 int GML_CLOCK_CLEAR_MASK ; 
 int GML_CLOCK_DETECT_BIT_SPDIF96 ; 
 int GML_CLOCK_DETECT_BIT_WORD96 ; 
 int GML_DOUBLE_SPEED_MODE ; 
 int GML_SPDIF_CLOCK ; 
 int GML_WORD_CLOCK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int set_sample_rate (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int switch_asic (struct echoaudio*,int) ; 
 int write_control_reg (struct echoaudio*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_input_clock(struct echoaudio *chip, u16 clock)
{
	u32 control_reg, clocks_from_dsp;
	int err;

	DE_ACT(("set_input_clock:\n"));

	/* Prevent two simultaneous calls to switch_asic() */
	if (atomic_read(&chip->opencount))
		return -EAGAIN;

	/* Mask off the clock select bits */
	control_reg = le32_to_cpu(chip->comm_page->control_register) &
		GML_CLOCK_CLEAR_MASK;
	clocks_from_dsp = le32_to_cpu(chip->comm_page->status_clocks);

	switch (clock) {
	case ECHO_CLOCK_INTERNAL:
		DE_ACT(("Set Mona clock to INTERNAL\n"));
		chip->input_clock = ECHO_CLOCK_INTERNAL;
		return set_sample_rate(chip, chip->sample_rate);
	case ECHO_CLOCK_SPDIF:
		if (chip->digital_mode == DIGITAL_MODE_ADAT)
			return -EAGAIN;
		spin_unlock_irq(&chip->lock);
		err = switch_asic(chip, clocks_from_dsp &
				  GML_CLOCK_DETECT_BIT_SPDIF96);
		spin_lock_irq(&chip->lock);
		if (err < 0)
			return err;
		DE_ACT(("Set Mona clock to SPDIF\n"));
		control_reg |= GML_SPDIF_CLOCK;
		if (clocks_from_dsp & GML_CLOCK_DETECT_BIT_SPDIF96)
			control_reg |= GML_DOUBLE_SPEED_MODE;
		else
			control_reg &= ~GML_DOUBLE_SPEED_MODE;
		break;
	case ECHO_CLOCK_WORD:
		DE_ACT(("Set Mona clock to WORD\n"));
		spin_unlock_irq(&chip->lock);
		err = switch_asic(chip, clocks_from_dsp &
				  GML_CLOCK_DETECT_BIT_WORD96);
		spin_lock_irq(&chip->lock);
		if (err < 0)
			return err;
		control_reg |= GML_WORD_CLOCK;
		if (clocks_from_dsp & GML_CLOCK_DETECT_BIT_WORD96)
			control_reg |= GML_DOUBLE_SPEED_MODE;
		else
			control_reg &= ~GML_DOUBLE_SPEED_MODE;
		break;
	case ECHO_CLOCK_ADAT:
		DE_ACT(("Set Mona clock to ADAT\n"));
		if (chip->digital_mode != DIGITAL_MODE_ADAT)
			return -EAGAIN;
		control_reg |= GML_ADAT_CLOCK;
		control_reg &= ~GML_DOUBLE_SPEED_MODE;
		break;
	default:
		DE_ACT(("Input clock 0x%x not supported for Mona\n", clock));
		return -EINVAL;
	}

	chip->input_clock = clock;
	return write_control_reg(chip, control_reg, TRUE);
}