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
 int /*<<< orphan*/  AC97_WM9711_OUT3VOL ; 
 int /*<<< orphan*/  AC97_WM97XX_TEST ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wolfson_init11(struct ac97_codec * codec)
{
	/* stop pop's during suspend/resume */
	codec->codec_write(codec, AC97_WM97XX_TEST,
		codec->codec_read(codec, AC97_WM97XX_TEST) & 0xffbf);

	/* set out3 volume */
	codec->codec_write(codec, AC97_WM9711_OUT3VOL, 0x0808);
	return 0;
}