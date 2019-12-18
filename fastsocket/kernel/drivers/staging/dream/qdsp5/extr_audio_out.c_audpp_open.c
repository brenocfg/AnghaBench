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
struct inode {int dummy; } ;
struct file {struct audio* private_data; } ;
struct audio {int dummy; } ;

/* Variables and functions */
 struct audio the_audio ; 

__attribute__((used)) static int audpp_open(struct inode *inode, struct file *file)
{
	struct audio *audio = &the_audio;

	file->private_data = audio;
	return 0;
}