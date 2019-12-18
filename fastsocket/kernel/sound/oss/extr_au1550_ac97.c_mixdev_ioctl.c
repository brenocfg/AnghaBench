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
struct ac97_codec {int (* mixer_ioctl ) (struct ac97_codec*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int stub1 (struct ac97_codec*,unsigned int,unsigned long) ; 

__attribute__((used)) static int
mixdev_ioctl(struct ac97_codec *codec, unsigned int cmd,
                        unsigned long arg)
{
	return codec->mixer_ioctl(codec, cmd, arg);
}