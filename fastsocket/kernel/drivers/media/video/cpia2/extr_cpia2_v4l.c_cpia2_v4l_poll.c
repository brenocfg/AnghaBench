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
struct poll_table_struct {int dummy; } ;
struct file {struct cpia2_fh* private_data; } ;
struct cpia2_fh {scalar_t__ prio; } ;
struct camera_data {int dummy; } ;

/* Variables and functions */
 unsigned int POLLERR ; 
 scalar_t__ V4L2_PRIORITY_RECORD ; 
 unsigned int cpia2_poll (struct camera_data*,struct file*,struct poll_table_struct*) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static unsigned int cpia2_v4l_poll(struct file *filp, struct poll_table_struct *wait)
{
	struct camera_data *cam = video_drvdata(filp);
	struct cpia2_fh *fh = filp->private_data;

	if(!cam)
		return POLLERR;

	/* Priority check */
	if(fh->prio != V4L2_PRIORITY_RECORD) {
		return POLLERR;
	}

	return cpia2_poll(cam, filp, wait);
}