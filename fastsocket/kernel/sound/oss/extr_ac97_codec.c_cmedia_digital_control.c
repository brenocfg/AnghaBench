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
typedef  int u16 ;
struct ac97_codec {int (* codec_read ) (struct ac97_codec*,int) ;int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int,int) ;} ;

/* Variables and functions */
 int AUDIO_DIGITAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int,int) ; 
 int stub3 (struct ac97_codec*,int) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int,int) ; 

__attribute__((used)) static int cmedia_digital_control(struct ac97_codec *codec, int slots, int rate, int mode)
{
	u16 cv;

	if(mode & AUDIO_DIGITAL)
		return -EINVAL;
		
	switch(rate)
	{
		case 0:		cv = 0x0001; break;	/* SPEN off */
		case 48000:	cv = 0x0009; break;	/* 48KHz digital */
		default:
			return -EINVAL;
	}
	codec->codec_write(codec, 0x2A, 0x05c4);
	codec->codec_write(codec, 0x6C, cv);
	
	/* Switch on mix to surround */
	cv = codec->codec_read(codec, 0x64);
	cv &= ~0x0200;
	if(mode)
		cv |= 0x0200;
	codec->codec_write(codec, 0x64, cv);
	return 0;
}