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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl_ref {int dummy; } ;
struct v4l2_ctrl_handler {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct v4l2_ctrl_ref* find_ref (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct v4l2_ctrl_ref *find_ref_lock(
		struct v4l2_ctrl_handler *hdl, u32 id)
{
	struct v4l2_ctrl_ref *ref = NULL;

	if (hdl) {
		mutex_lock(&hdl->lock);
		ref = find_ref(hdl, id);
		mutex_unlock(&hdl->lock);
	}
	return ref;
}