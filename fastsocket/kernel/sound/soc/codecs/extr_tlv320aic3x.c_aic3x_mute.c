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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDAC_VOL ; 
 int MUTE_ON ; 
 int /*<<< orphan*/  RDAC_VOL ; 
 int aic3x_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic3x_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic3x_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_codec *codec = dai->codec;
	u8 ldac_reg = aic3x_read_reg_cache(codec, LDAC_VOL) & ~MUTE_ON;
	u8 rdac_reg = aic3x_read_reg_cache(codec, RDAC_VOL) & ~MUTE_ON;

	if (mute) {
		aic3x_write(codec, LDAC_VOL, ldac_reg | MUTE_ON);
		aic3x_write(codec, RDAC_VOL, rdac_reg | MUTE_ON);
	} else {
		aic3x_write(codec, LDAC_VOL, ldac_reg);
		aic3x_write(codec, RDAC_VOL, rdac_reg);
	}

	return 0;
}