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
struct ac97_codec {int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int,int) ;} ;

/* Variables and functions */
 int AUDIO_DIGITAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int,int) ; 

__attribute__((used)) static int crystal_digital_control(struct ac97_codec *codec, int slots, int rate, int mode)
{
	u16 cv;

	if(mode & AUDIO_DIGITAL)
		return -EINVAL;
		
	switch(rate)
	{
		case 0: cv = 0x0; break;	/* SPEN off */
		case 48000: cv = 0x8004; break;	/* 48KHz digital */
		case 44100: cv = 0x8104; break;	/* 44.1KHz digital */
		case 32768: 			/* 32Khz */
		default:
			return -EINVAL;
	}
	codec->codec_write(codec, 0x68, cv);
	return 0;
}