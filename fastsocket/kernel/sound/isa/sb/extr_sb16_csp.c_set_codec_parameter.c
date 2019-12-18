#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_sb {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  command_seq (struct snd_sb*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,int) ; 
 unsigned char snd_sbdsp_get_byte (struct snd_sb*) ; 

__attribute__((used)) static int set_codec_parameter(struct snd_sb *chip, unsigned char par, unsigned char val)
{
	unsigned char dsp_cmd[3];

	dsp_cmd[0] = 0x05;	/* CSP set codec parameter */
	dsp_cmd[1] = val;	/* Parameter value */
	dsp_cmd[2] = par;	/* Parameter */
	command_seq(chip, dsp_cmd, 3);
	snd_sbdsp_command(chip, 0x03);	/* DSP read? */
	if (snd_sbdsp_get_byte(chip) != par)
		return -EIO;
	return 0;
}