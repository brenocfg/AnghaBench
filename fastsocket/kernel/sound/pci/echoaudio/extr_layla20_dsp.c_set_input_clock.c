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
typedef  int u16 ;
struct echoaudio {int input_clock; TYPE_1__* comm_page; scalar_t__ sample_rate; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DSP_VC_UPDATE_CLOCKS ; 
#define  ECHO_CLOCK_INTERNAL 131 
#define  ECHO_CLOCK_SPDIF 130 
#define  ECHO_CLOCK_SUPER 129 
#define  ECHO_CLOCK_WORD 128 
 int EINVAL ; 
 int LAYLA20_CLOCK_INTERNAL ; 
 int LAYLA20_CLOCK_SPDIF ; 
 int LAYLA20_CLOCK_SUPER ; 
 int LAYLA20_CLOCK_WORD ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sample_rate (struct echoaudio*,scalar_t__) ; 

__attribute__((used)) static int set_input_clock(struct echoaudio *chip, u16 clock_source)
{
	u16 clock;
	u32 rate;

	DE_ACT(("set_input_clock:\n"));
	rate = 0;
	switch (clock_source) {
	case ECHO_CLOCK_INTERNAL:
		DE_ACT(("Set Layla20 clock to INTERNAL\n"));
		rate = chip->sample_rate;
		clock = LAYLA20_CLOCK_INTERNAL;
		break;
	case ECHO_CLOCK_SPDIF:
		DE_ACT(("Set Layla20 clock to SPDIF\n"));
		clock = LAYLA20_CLOCK_SPDIF;
		break;
	case ECHO_CLOCK_WORD:
		DE_ACT(("Set Layla20 clock to WORD\n"));
		clock = LAYLA20_CLOCK_WORD;
		break;
	case ECHO_CLOCK_SUPER:
		DE_ACT(("Set Layla20 clock to SUPER\n"));
		clock = LAYLA20_CLOCK_SUPER;
		break;
	default:
		DE_ACT(("Input clock 0x%x not supported for Layla24\n",
			clock_source));
		return -EINVAL;
	}
	chip->input_clock = clock_source;

	chip->comm_page->input_clock = cpu_to_le16(clock);
	clear_handshake(chip);
	send_vector(chip, DSP_VC_UPDATE_CLOCKS);

	if (rate)
		set_sample_rate(chip, rate);

	return 0;
}