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
struct snd_mpu401 {int /*<<< orphan*/  (* close_input ) (struct snd_mpu401*) ;int /*<<< orphan*/  mode; int /*<<< orphan*/ * substream_input; } ;
struct TYPE_2__ {struct snd_mpu401* private_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_INPUT ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_OUTPUT ; 
 int /*<<< orphan*/  MPU401_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_mpu401_uart_cmd (struct snd_mpu401*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_mpu401*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mpu401_uart_input_close(struct snd_rawmidi_substream *substream)
{
	struct snd_mpu401 *mpu;
	int err = 0;

	mpu = substream->rmidi->private_data;
	clear_bit(MPU401_MODE_BIT_INPUT, &mpu->mode);
	mpu->substream_input = NULL;
	if (! test_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode))
		err = snd_mpu401_uart_cmd(mpu, MPU401_RESET, 0);
	if (mpu->close_input)
		mpu->close_input(mpu);
	if (err)
		return -EIO;
	return 0;
}