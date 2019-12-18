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
struct vga_switcheroo_client {int active; scalar_t__ pwr_state; int /*<<< orphan*/  id; int /*<<< orphan*/  pdev; TYPE_2__* ops; scalar_t__ fb_info; } ;
struct fb_event {scalar_t__ info; } ;
struct TYPE_6__ {TYPE_1__* handler; int /*<<< orphan*/  clients; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reprobe ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int (* switchto ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FB_EVENT_REMAP_ALL_CONSOLE ; 
 scalar_t__ VGA_SWITCHEROO_OFF ; 
 scalar_t__ VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  fb_notifier_call_chain (int /*<<< orphan*/ ,struct fb_event*) ; 
 struct vga_switcheroo_client* find_active_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_audio_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switchoff (struct vga_switcheroo_client*) ; 
 TYPE_3__ vgasr_priv ; 

__attribute__((used)) static int vga_switchto_stage2(struct vga_switcheroo_client *new_client)
{
	int ret;
	struct vga_switcheroo_client *active;

	active = find_active_client(&vgasr_priv.clients);
	if (!active)
		return 0;

	active->active = false;

	set_audio_state(active->id, VGA_SWITCHEROO_OFF);

	if (new_client->fb_info) {
		struct fb_event event;
		event.info = new_client->fb_info;
		fb_notifier_call_chain(FB_EVENT_REMAP_ALL_CONSOLE, &event);
	}

	ret = vgasr_priv.handler->switchto(new_client->id);
	if (ret)
		return ret;

	if (new_client->ops->reprobe)
		new_client->ops->reprobe(new_client->pdev);

	if (active->pwr_state == VGA_SWITCHEROO_ON)
		vga_switchoff(active);

	set_audio_state(new_client->id, VGA_SWITCHEROO_ON);

	new_client->active = true;
	return 0;
}