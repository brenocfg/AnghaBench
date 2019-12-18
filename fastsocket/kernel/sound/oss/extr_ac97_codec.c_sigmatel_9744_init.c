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
struct ac97_codec {int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_SIGMATEL_BIAS1 ; 
 int /*<<< orphan*/  AC97_SIGMATEL_BIAS2 ; 
 int /*<<< orphan*/  AC97_SIGMATEL_CIC1 ; 
 int /*<<< orphan*/  AC97_SIGMATEL_CIC2 ; 
 int /*<<< orphan*/  AC97_SIGMATEL_MULTICHN ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct ac97_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sigmatel_9744_init(struct ac97_codec * codec)
{
	// patch for SigmaTel
	codec->codec_write(codec, AC97_SIGMATEL_CIC1, 0xabba);
	codec->codec_write(codec, AC97_SIGMATEL_CIC2, 0x0000); // is this correct? --jk
	codec->codec_write(codec, AC97_SIGMATEL_BIAS1, 0xabba);
	codec->codec_write(codec, AC97_SIGMATEL_BIAS2, 0x0002);
	codec->codec_write(codec, AC97_SIGMATEL_MULTICHN, 0x0000);
	return 0;
}