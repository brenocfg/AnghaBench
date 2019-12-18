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
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int,int) ; 
 int stub2 (struct ac97_codec*,int) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct ac97_codec*,int,int) ; 

__attribute__((used)) static int cmedia_init(struct ac97_codec *codec)
{
	/* Initialise the CMedia 9739 */
	/*
		We could set various options here
		Register 0x20 bit 0x100 sets mic as center bass
		Also do multi_channel_ctrl &=~0x3000 |=0x1000
		
		For now we set up the GPIO and PC beep 
	*/
	
	u16 v;
	
	/* MIC */
	codec->codec_write(codec, 0x64, 0x3000);
	v = codec->codec_read(codec, 0x64);
	v &= ~0x8000;
	codec->codec_write(codec, 0x64, v);
	codec->codec_write(codec, 0x70, 0x0100);
	codec->codec_write(codec, 0x72, 0x0020);
	return 0;
}