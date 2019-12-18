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
struct notifier_block {int dummy; } ;
struct fb_videomode {int /*<<< orphan*/  console; int /*<<< orphan*/  framebuffer; } ;
struct fb_info {int node; } ;
struct fb_event {struct fb_videomode* data; struct fb_info* info; } ;
struct fb_con2fbmap {int /*<<< orphan*/  console; int /*<<< orphan*/  framebuffer; } ;
struct fb_blit_caps {int /*<<< orphan*/  console; int /*<<< orphan*/  framebuffer; } ;

/* Variables and functions */
#define  FB_EVENT_BLANK 141 
#define  FB_EVENT_FB_REGISTERED 140 
#define  FB_EVENT_FB_UNBIND 139 
#define  FB_EVENT_FB_UNREGISTERED 138 
#define  FB_EVENT_GET_CONSOLE_MAP 137 
#define  FB_EVENT_GET_REQ 136 
#define  FB_EVENT_MODE_CHANGE 135 
#define  FB_EVENT_MODE_CHANGE_ALL 134 
#define  FB_EVENT_MODE_DELETE 133 
#define  FB_EVENT_NEW_MODELIST 132 
#define  FB_EVENT_REMAP_ALL_CONSOLE 131 
#define  FB_EVENT_RESUME 130 
#define  FB_EVENT_SET_CONSOLE_MAP 129 
#define  FB_EVENT_SUSPEND 128 
 int /*<<< orphan*/ * con2fb_map ; 
 int /*<<< orphan*/  fbcon_fb_blanked (struct fb_info*,int) ; 
 int fbcon_fb_registered (struct fb_info*) ; 
 int fbcon_fb_unbind (int) ; 
 int fbcon_fb_unregistered (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_get_requirement (struct fb_info*,struct fb_videomode*) ; 
 scalar_t__ fbcon_has_exited ; 
 int fbcon_mode_deleted (struct fb_info*,struct fb_videomode*) ; 
 int /*<<< orphan*/  fbcon_modechanged (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_new_modelist (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_remap_all (int) ; 
 int /*<<< orphan*/  fbcon_resumed (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_set_all_vcs (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_suspended (struct fb_info*) ; 
 int set_con2fb_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fbcon_event_notify(struct notifier_block *self,
			      unsigned long action, void *data)
{
	struct fb_event *event = data;
	struct fb_info *info = event->info;
	struct fb_videomode *mode;
	struct fb_con2fbmap *con2fb;
	struct fb_blit_caps *caps;
	int idx, ret = 0;

	/*
	 * ignore all events except driver registration and deregistration
	 * if fbcon is not active
	 */
	if (fbcon_has_exited && !(action == FB_EVENT_FB_REGISTERED ||
				  action == FB_EVENT_FB_UNREGISTERED))
		goto done;

	switch(action) {
	case FB_EVENT_SUSPEND:
		fbcon_suspended(info);
		break;
	case FB_EVENT_RESUME:
		fbcon_resumed(info);
		break;
	case FB_EVENT_MODE_CHANGE:
		fbcon_modechanged(info);
		break;
	case FB_EVENT_MODE_CHANGE_ALL:
		fbcon_set_all_vcs(info);
		break;
	case FB_EVENT_MODE_DELETE:
		mode = event->data;
		ret = fbcon_mode_deleted(info, mode);
		break;
	case FB_EVENT_FB_UNBIND:
		idx = info->node;
		ret = fbcon_fb_unbind(idx);
		break;
	case FB_EVENT_FB_REGISTERED:
		ret = fbcon_fb_registered(info);
		break;
	case FB_EVENT_FB_UNREGISTERED:
		ret = fbcon_fb_unregistered(info);
		break;
	case FB_EVENT_SET_CONSOLE_MAP:
		con2fb = event->data;
		ret = set_con2fb_map(con2fb->console - 1,
				     con2fb->framebuffer, 1);
		break;
	case FB_EVENT_GET_CONSOLE_MAP:
		con2fb = event->data;
		con2fb->framebuffer = con2fb_map[con2fb->console - 1];
		break;
	case FB_EVENT_BLANK:
		fbcon_fb_blanked(info, *(int *)event->data);
		break;
	case FB_EVENT_NEW_MODELIST:
		fbcon_new_modelist(info);
		break;
	case FB_EVENT_GET_REQ:
		caps = event->data;
		fbcon_get_requirement(info, caps);
		break;
	case FB_EVENT_REMAP_ALL_CONSOLE:
		idx = info->node;
		fbcon_remap_all(idx);
		break;
	}
done:
	return ret;
}