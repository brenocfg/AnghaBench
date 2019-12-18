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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_mpu401 {int (* open_input ) (struct snd_mpu401*) ;int /*<<< orphan*/  (* close_input ) (struct snd_mpu401*) ;int /*<<< orphan*/  mode; struct snd_rawmidi_substream* substream_input; } ;
struct TYPE_2__ {struct snd_mpu401* private_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_INPUT ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_OUTPUT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_mpu401_do_reset (struct snd_mpu401*) ; 
 int stub1 (struct snd_mpu401*) ; 
 int /*<<< orphan*/  stub2 (struct snd_mpu401*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mpu401_uart_input_open(struct snd_rawmidi_substream *substream)
{
	struct snd_mpu401 *mpu;
	int err;

	mpu = substream->rmidi->private_data;
	if (mpu->open_input && (err = mpu->open_input(mpu)) < 0)
		return err;
	if (! test_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode)) {
		if (snd_mpu401_do_reset(mpu) < 0)
			goto error_out;
	}
	mpu->substream_input = substream;
	set_bit(MPU401_MODE_BIT_INPUT, &mpu->mode);
	return 0;

error_out:
	if (mpu->open_input && mpu->close_input)
		mpu->close_input(mpu);
	return -EIO;
}