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
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  serialize_lock; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 unsigned int VIDIOC_DQEVENT ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 long ivtv_serialized_ioctl (struct ivtv*,struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

long ivtv_v4l2_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct ivtv_open_id *id = fh2id(filp->private_data);
	struct ivtv *itv = id->itv;
	long res;

	/* DQEVENT can block, so this should not run with the serialize lock */
	if (cmd == VIDIOC_DQEVENT)
		return ivtv_serialized_ioctl(itv, filp, cmd, arg);
	mutex_lock(&itv->serialize_lock);
	res = ivtv_serialized_ioctl(itv, filp, cmd, arg);
	mutex_unlock(&itv->serialize_lock);
	return res;
}