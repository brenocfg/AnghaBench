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
struct snd_soc_codec {unsigned int* reg_cache; unsigned int reg_cache_size; int (* hw_write ) (int /*<<< orphan*/ ,unsigned int*,int) ;int /*<<< orphan*/  control_data; int /*<<< orphan*/  volatile_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int snd_soc_7_9_write(struct snd_soc_codec *codec, unsigned int reg,
			     unsigned int value)
{
	u16 *cache = codec->reg_cache;
	u8 data[2];
	int ret;

	BUG_ON(codec->volatile_register);

	data[0] = (reg << 1) | ((value >> 8) & 0x0001);
	data[1] = value & 0x00ff;

	if (reg < codec->reg_cache_size)
		cache[reg] = value;
	ret = codec->hw_write(codec->control_data, data, 2);
	if (ret == 2)
		return 0;
	if (ret < 0)
		return ret;
	else
		return -EIO;
}