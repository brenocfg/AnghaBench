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
typedef  int u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct snd_soc_codec {int* reg_cache; int reg_cache_size; struct spi_device* control_data; } ;

/* Variables and functions */
 int EIO ; 
 int ad1938_read_reg (struct snd_soc_codec*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ad1938_fill_cache(struct snd_soc_codec *codec)
{
	int i;
	u8 *reg_cache = codec->reg_cache;
	struct spi_device *spi = codec->control_data;

	for (i = 0; i < codec->reg_cache_size; i++) {
		int ret = ad1938_read_reg(codec, i);
		if (ret == -EIO) {
			dev_err(&spi->dev, "AD1938 SPI read failure\n");
			return ret;
		}
		reg_cache[i] = ret;
	}

	return 0;
}