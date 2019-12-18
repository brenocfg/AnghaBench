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
struct snd_soc_codec {int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  aic3x_write_reg_cache (struct snd_soc_codec*,unsigned int,unsigned int) ; 
 unsigned int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aic3x_read(struct snd_soc_codec *codec, unsigned int reg,
		      u8 *value)
{
	*value = reg & 0xff;

	value[0] = i2c_smbus_read_byte_data(codec->control_data, value[0]);

	aic3x_write_reg_cache(codec, reg, *value);
	return 0;
}