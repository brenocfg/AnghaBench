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
struct echoaudio {TYPE_1__* comm_page; } ;
struct TYPE_2__ {scalar_t__* midi_input; } ;

/* Variables and functions */
 int CHI32_STATUS_IRQ ; 
 int /*<<< orphan*/  CHI32_STATUS_REG ; 
 int /*<<< orphan*/  DSP_VC_ACK_INT ; 
 int get_dsp_register (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int midi_service_irq (struct echoaudio*) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int service_irq(struct echoaudio *chip)
{
	int st;

	/* Read the DSP status register and see if this DSP generated this interrupt */
	if (get_dsp_register(chip, CHI32_STATUS_REG) & CHI32_STATUS_IRQ) {
		st = 0;
#ifdef ECHOCARD_HAS_MIDI
		/* Get and parse midi data if present */
		if (chip->comm_page->midi_input[0])	/* The count is at index 0 */
			st = midi_service_irq(chip);	/* Returns how many midi bytes we received */
#endif
		/* Clear the hardware interrupt */
		chip->comm_page->midi_input[0] = 0;
		send_vector(chip, DSP_VC_ACK_INT);
		return st;
	}
	return -1;
}