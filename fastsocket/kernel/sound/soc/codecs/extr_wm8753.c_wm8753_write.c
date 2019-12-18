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
typedef  unsigned int u8 ;
struct snd_soc_codec {int (* hw_write ) (int /*<<< orphan*/ ,unsigned int*,int) ;int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int EIO ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  wm8753_write_reg_cache (struct snd_soc_codec*,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm8753_write(struct snd_soc_codec *codec, unsigned int reg,
	unsigned int value)
{
	u8 data[2];

	/* data is
	 *   D15..D9 WM8753 register offset
	 *   D8...D0 register data
	 */
	data[0] = (reg << 1) | ((value >> 8) & 0x0001);
	data[1] = value & 0x00ff;

	wm8753_write_reg_cache(codec, reg, value);
	if (codec->hw_write(codec->control_data, data, 2) == 2)
		return 0;
	else
		return -EIO;
}