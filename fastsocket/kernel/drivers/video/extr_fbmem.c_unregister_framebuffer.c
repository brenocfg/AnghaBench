#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ addr; } ;
struct fb_info {int node; TYPE_2__* fbops; int /*<<< orphan*/  modelist; TYPE_1__ pixmap; } ;
struct fb_event {struct fb_info* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fb_destroy ) (struct fb_info*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FB_EVENT_FB_UNBIND ; 
 int /*<<< orphan*/  FB_EVENT_FB_UNREGISTERED ; 
 int /*<<< orphan*/  FB_MAJOR ; 
 int FB_PIXMAP_DEFAULT ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_class ; 
 int /*<<< orphan*/  fb_cleanup_device (struct fb_info*) ; 
 int /*<<< orphan*/  fb_destroy_modelist (int /*<<< orphan*/ *) ; 
 int fb_notifier_call_chain (int /*<<< orphan*/ ,struct fb_event*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  lock_fb_info (struct fb_info*) ; 
 int /*<<< orphan*/  num_registered_fb ; 
 int /*<<< orphan*/ ** registered_fb ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 
 int /*<<< orphan*/  unlock_fb_info (struct fb_info*) ; 

int
unregister_framebuffer(struct fb_info *fb_info)
{
	struct fb_event event;
	int i, ret = 0;

	i = fb_info->node;
	if (!registered_fb[i]) {
		ret = -EINVAL;
		goto done;
	}


	if (!lock_fb_info(fb_info))
		return -ENODEV;
	event.info = fb_info;
	ret = fb_notifier_call_chain(FB_EVENT_FB_UNBIND, &event);
	unlock_fb_info(fb_info);

	if (ret) {
		ret = -EINVAL;
		goto done;
	}

	if (fb_info->pixmap.addr &&
	    (fb_info->pixmap.flags & FB_PIXMAP_DEFAULT))
		kfree(fb_info->pixmap.addr);
	fb_destroy_modelist(&fb_info->modelist);
	registered_fb[i]=NULL;
	num_registered_fb--;
	fb_cleanup_device(fb_info);
	device_destroy(fb_class, MKDEV(FB_MAJOR, i));
	event.info = fb_info;
	fb_notifier_call_chain(FB_EVENT_FB_UNREGISTERED, &event);

	/* this may free fb info */
	if (fb_info->fbops->fb_destroy)
		fb_info->fbops->fb_destroy(fb_info);
done:
	return ret;
}