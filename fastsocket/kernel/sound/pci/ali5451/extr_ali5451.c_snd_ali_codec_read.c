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
 unsigned short snd_ali_codec_peek (struct snd_ali*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_ali_printk (char*,unsigned short) ; 

__attribute__((used)) static unsigned short snd_ali_codec_read(struct snd_ac97 *ac97,
					 unsigned short reg)
{
	struct snd_ali *codec = ac97->private_data;

	snd_ali_printk("codec_read reg=%xh.\n", reg);
	return snd_ali_codec_peek(codec, ac97->num, reg);
}