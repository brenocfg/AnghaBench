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
struct snd_soc_codec {unsigned short (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_REG_VOICE_IF ; 
 unsigned short TWL4030_VIF_DIN_EN ; 
 unsigned short TWL4030_VIF_DOUT_EN ; 
 unsigned short TWL4030_VIF_EN ; 
 unsigned short stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int zoom2_twl4030_voice_init(struct snd_soc_codec *codec)
{
	unsigned short reg;

	/* Enable voice interface */
	reg = codec->read(codec, TWL4030_REG_VOICE_IF);
	reg |= TWL4030_VIF_DIN_EN | TWL4030_VIF_DOUT_EN | TWL4030_VIF_EN;
	codec->write(codec, TWL4030_REG_VOICE_IF, reg);

	return 0;
}