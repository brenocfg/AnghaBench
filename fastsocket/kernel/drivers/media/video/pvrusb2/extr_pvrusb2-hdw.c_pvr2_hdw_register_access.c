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
typedef  void* u64 ;
struct v4l2_dbg_match {int dummy; } ;
struct v4l2_dbg_register {void* val; void* reg; struct v4l2_dbg_match match; } ;
struct pvr2_hdw {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENOSYS ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  g_register ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_register*) ; 

int pvr2_hdw_register_access(struct pvr2_hdw *hdw,
			     struct v4l2_dbg_match *match, u64 reg_id,
			     int setFl, u64 *val_ptr)
{
#ifdef CONFIG_VIDEO_ADV_DEBUG
	struct v4l2_dbg_register req;
	int stat = 0;
	int okFl = 0;

	if (!capable(CAP_SYS_ADMIN)) return -EPERM;

	req.match = *match;
	req.reg = reg_id;
	if (setFl) req.val = *val_ptr;
	/* It would be nice to know if a sub-device answered the request */
	v4l2_device_call_all(&hdw->v4l2_dev, 0, core, g_register, &req);
	if (!setFl) *val_ptr = req.val;
	if (okFl) {
		return stat;
	}
	return -EINVAL;
#else
	return -ENOSYS;
#endif
}