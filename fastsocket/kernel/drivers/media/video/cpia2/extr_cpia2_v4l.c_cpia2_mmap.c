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
struct vm_area_struct {int dummy; } ;
struct file {struct cpia2_fh* private_data; } ;
struct cpia2_fh {scalar_t__ prio; int mmapped; } ;
struct camera_data {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ V4L2_PRIORITY_RECORD ; 
 int cpia2_remap_buffer (struct camera_data*,struct vm_area_struct*) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_mmap(struct file *file, struct vm_area_struct *area)
{
	struct camera_data *cam = video_drvdata(file);
	int retval;

	/* Priority check */
	struct cpia2_fh *fh = file->private_data;
	if(fh->prio != V4L2_PRIORITY_RECORD) {
		return -EBUSY;
	}

	retval = cpia2_remap_buffer(cam, area);

	if(!retval)
		fh->mmapped = 1;
	return retval;
}