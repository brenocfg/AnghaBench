#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mdp_img {int /*<<< orphan*/  memory_id; } ;
struct file {TYPE_1__* f_dentry; } ;
struct TYPE_5__ {unsigned long smem_start; unsigned long smem_len; } ;
struct fb_info {TYPE_2__ fix; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_rdev; } ;
struct TYPE_4__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 scalar_t__ FB_MAJOR ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 struct file* fget_light (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 

int get_img(struct mdp_img *img, struct fb_info *info,
	    unsigned long *start, unsigned long *len,
	    struct file **filep)
{
	int put_needed, ret = 0;
	struct file *file;
	unsigned long vstart;

	file = fget_light(img->memory_id, &put_needed);
	if (file == NULL)
		return -1;

	if (MAJOR(file->f_dentry->d_inode->i_rdev) == FB_MAJOR) {
		*start = info->fix.smem_start;
		*len = info->fix.smem_len;
	} else
		ret = -1;
	fput_light(file, put_needed);

	return ret;
}