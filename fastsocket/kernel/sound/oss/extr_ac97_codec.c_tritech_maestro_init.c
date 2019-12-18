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
 int /*<<< orphan*/  stub1 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ac97_codec*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct ac97_codec*,int,int) ; 

__attribute__((used)) static int tritech_maestro_init(struct ac97_codec * codec)
{
	/* no idea what this does */
	codec->codec_write(codec, 0x2A, 0x0001);
	codec->codec_write(codec, 0x2C, 0x0000);
	codec->codec_write(codec, 0x2C, 0XFFFF);
	return 0;
}