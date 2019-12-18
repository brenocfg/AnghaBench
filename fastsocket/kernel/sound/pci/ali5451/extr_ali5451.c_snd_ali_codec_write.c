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
struct snd_ali {int dummy; } ;
struct snd_ac97 {int /*<<< orphan*/  num; struct snd_ali* private_data; } ;

/* Variables and functions */
 unsigned short AC97_GPIO_STATUS ; 
 int /*<<< orphan*/  ALI_AC97_GPIO ; 
 unsigned short ALI_AC97_GPIO_DATA_SHIFT ; 
 unsigned short ALI_AC97_GPIO_ENABLE ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_codec_poke (struct snd_ali*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  snd_ali_printk (char*,unsigned short,unsigned short) ; 

__attribute__((used)) static void snd_ali_codec_write(struct snd_ac97 *ac97,
				unsigned short reg,
				unsigned short val )
{
	struct snd_ali *codec = ac97->private_data;

	snd_ali_printk("codec_write: reg=%xh data=%xh.\n", reg, val);
	if (reg == AC97_GPIO_STATUS) {
		outl((val << ALI_AC97_GPIO_DATA_SHIFT) | ALI_AC97_GPIO_ENABLE,
		     ALI_REG(codec, ALI_AC97_GPIO));
		return;
	}
	snd_ali_codec_poke(codec, ac97->num, reg, val);
	return ;
}