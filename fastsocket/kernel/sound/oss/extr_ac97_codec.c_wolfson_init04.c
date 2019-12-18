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
struct ac97_codec {int (* codec_read ) (struct ac97_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PCMOUT_VOL ; 
 int /*<<< orphan*/  AC97_SURROUND_MASTER ; 
 int /*<<< orphan*/  AC97_WM9704_RPCM_VOL ; 
 int /*<<< orphan*/  AC97_WM97XX_FMIXER_VOL ; 
 int /*<<< orphan*/  AC97_WM97XX_RMIXER_VOL ; 
 int /*<<< orphan*/  AC97_WM97XX_TEST ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int stub5 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wolfson_init04(struct ac97_codec * codec)
{
	codec->codec_write(codec, AC97_WM97XX_FMIXER_VOL, 0x0808);
	codec->codec_write(codec, AC97_WM97XX_RMIXER_VOL, 0x0808);

	// patch for DVD noise
	codec->codec_write(codec, AC97_WM97XX_TEST, 0x0200);

	// init vol as PCM vol
	codec->codec_write(codec, AC97_WM9704_RPCM_VOL,
		codec->codec_read(codec, AC97_PCMOUT_VOL));

	/* set rear surround volume */
	codec->codec_write(codec, AC97_SURROUND_MASTER, 0x0000);
	return 0;
}