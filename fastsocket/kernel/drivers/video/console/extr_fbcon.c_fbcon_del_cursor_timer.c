#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fbcon_ops {int flags; int /*<<< orphan*/  cursor_timer; } ;
struct TYPE_2__ {scalar_t__ func; } ;
struct fb_info {TYPE_1__ queue; struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int FBCON_FLAGS_CURSOR_TIMER ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ fb_flashcursor ; 

__attribute__((used)) static void fbcon_del_cursor_timer(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;

	if (info->queue.func == fb_flashcursor &&
	    ops->flags & FBCON_FLAGS_CURSOR_TIMER) {
		del_timer_sync(&ops->cursor_timer);
		ops->flags &= ~FBCON_FLAGS_CURSOR_TIMER;
	}
}