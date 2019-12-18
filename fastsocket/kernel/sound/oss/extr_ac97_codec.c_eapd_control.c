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
 int /*<<< orphan*/  AC97_POWER_CONTROL ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct ac97_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eapd_control(struct ac97_codec * codec, int on)
{
	if(on)
		codec->codec_write(codec, AC97_POWER_CONTROL,
			codec->codec_read(codec, AC97_POWER_CONTROL)|0x8000);
	else
		codec->codec_write(codec, AC97_POWER_CONTROL,
			codec->codec_read(codec, AC97_POWER_CONTROL)&~0x8000);
	return 0;
}