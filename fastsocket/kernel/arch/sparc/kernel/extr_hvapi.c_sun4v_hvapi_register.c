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
struct api_info {unsigned long major; unsigned long minor; int flags; scalar_t__ refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int FLAG_PRE_API ; 
 unsigned long HV_EBADTRAP ; 
 unsigned long HV_ENOTSUPPORTED ; 
 unsigned long HV_EOK ; 
 struct api_info* __get_info (unsigned long) ; 
 int /*<<< orphan*/  __get_ref (struct api_info*) ; 
 int /*<<< orphan*/  hvapi_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long sun4v_set_version (unsigned long,unsigned long,unsigned long,unsigned long*) ; 

int sun4v_hvapi_register(unsigned long group, unsigned long major,
			 unsigned long *minor)
{
	struct api_info *p;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&hvapi_lock, flags);
	p = __get_info(group);
	ret = -EINVAL;
	if (p) {
		if (p->refcnt) {
			ret = -EINVAL;
			if (p->major == major) {
				*minor = p->minor;
				ret = 0;
			}
		} else {
			unsigned long actual_minor;
			unsigned long hv_ret;

			hv_ret = sun4v_set_version(group, major, *minor,
						   &actual_minor);
			ret = -EINVAL;
			if (hv_ret == HV_EOK) {
				*minor = actual_minor;
				p->major = major;
				p->minor = actual_minor;
				ret = 0;
			} else if (hv_ret == HV_EBADTRAP ||
				   hv_ret == HV_ENOTSUPPORTED) {
				if (p->flags & FLAG_PRE_API) {
					if (major == 1) {
						p->major = 1;
						p->minor = 0;
						*minor = 0;
						ret = 0;
					}
				}
			}
		}

		if (ret == 0)
			__get_ref(p);
	}
	spin_unlock_irqrestore(&hvapi_lock, flags);

	return ret;
}