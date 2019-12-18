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
struct snd_mixer_oss_file {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 long snd_mixer_oss_ioctl1 (struct snd_mixer_oss_file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long snd_mixer_oss_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return snd_mixer_oss_ioctl1((struct snd_mixer_oss_file *) file->private_data, cmd, arg);
}