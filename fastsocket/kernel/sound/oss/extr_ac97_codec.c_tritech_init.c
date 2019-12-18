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
struct ac97_codec {int /*<<< orphan*/  (* codec_write ) (struct ac97_codec*,int,int) ;} ;

/* Variables and functions */
 int AC97_RESERVED_3A ; 
 int AC97_SURROUND_MASTER ; 
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct ac97_codec*,int,int) ; 

__attribute__((used)) static int tritech_init(struct ac97_codec * codec)
{
	codec->codec_write(codec, 0x26, 0x0300);
	codec->codec_write(codec, 0x26, 0x0000);
	codec->codec_write(codec, AC97_SURROUND_MASTER, 0x0000);
	codec->codec_write(codec, AC97_RESERVED_3A, 0x0000);
	return 0;
}