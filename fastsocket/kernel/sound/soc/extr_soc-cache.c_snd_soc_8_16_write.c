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
typedef  unsigned int u16 ;
struct snd_soc_codec {unsigned int* reg_cache; int (* hw_write ) (int /*<<< orphan*/ ,unsigned int*,int) ;int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  snd_soc_codec_volatile_register (struct snd_soc_codec*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int snd_soc_8_16_write(struct snd_soc_codec *codec, unsigned int reg,
			      unsigned int value)
{
	u16 *reg_cache = codec->reg_cache;
	u8 data[3];

	data[0] = reg;
	data[1] = (value >> 8) & 0xff;
	data[2] = value & 0xff;

	if (!snd_soc_codec_volatile_register(codec, reg))
		reg_cache[reg] = value;

	if (codec->hw_write(codec->control_data, data, 3) == 3)
		return 0;
	else
		return -EIO;
}