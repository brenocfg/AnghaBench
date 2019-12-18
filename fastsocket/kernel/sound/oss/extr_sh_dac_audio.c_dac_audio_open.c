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
struct file {int f_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  dac_audio_start () ; 
 int in_use ; 

__attribute__((used)) static int dac_audio_open(struct inode *inode, struct file *file)
{
	if (file->f_mode & FMODE_READ)
		return -ENODEV;
	if (in_use)
		return -EBUSY;

	in_use = 1;

	dac_audio_start();

	return 0;
}