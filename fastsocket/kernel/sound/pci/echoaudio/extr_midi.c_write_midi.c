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
typedef  int /*<<< orphan*/  u8 ;
struct echoaudio {TYPE_1__* comm_page; } ;
struct TYPE_2__ {int* midi_output; scalar_t__ midi_out_free_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHI32_STATUS_REG ; 
 int CHI32_STATUS_REG_HF4 ; 
 int /*<<< orphan*/  DE_MID (char*) ; 
 int /*<<< orphan*/  DSP_VC_MIDI_WRITE ; 
 int EINVAL ; 
 int EIO ; 
 int MIDI_OUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int get_dsp_register (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int write_midi(struct echoaudio *chip, u8 *data, int bytes)
{
	if (snd_BUG_ON(bytes <= 0 || bytes >= MIDI_OUT_BUFFER_SIZE))
		return -EINVAL;

	if (wait_handshake(chip))
		return -EIO;

	/* HF4 indicates that it is safe to write MIDI output data */
	if (! (get_dsp_register(chip, CHI32_STATUS_REG) & CHI32_STATUS_REG_HF4))
		return 0;

	chip->comm_page->midi_output[0] = bytes;
	memcpy(&chip->comm_page->midi_output[1], data, bytes);
	chip->comm_page->midi_out_free_count = 0;
	clear_handshake(chip);
	send_vector(chip, DSP_VC_MIDI_WRITE);
	DE_MID(("write_midi: %d\n", bytes));
	return bytes;
}