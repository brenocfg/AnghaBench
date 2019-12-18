#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct fbcon_ops {int flags; TYPE_1__ cursor_timer; } ;
struct TYPE_5__ {scalar_t__ func; } ;
struct fb_info {TYPE_3__ queue; struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int FBCON_FLAGS_CURSOR_TIMER ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  cursor_timer_handler ; 
 scalar_t__ fb_flashcursor ; 
 int /*<<< orphan*/  fbcon_cursor_noblink ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void fbcon_add_cursor_timer(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;

	if ((!info->queue.func || info->queue.func == fb_flashcursor) &&
	    !(ops->flags & FBCON_FLAGS_CURSOR_TIMER) &&
	    !fbcon_cursor_noblink) {
		if (!info->queue.func)
			INIT_WORK(&info->queue, fb_flashcursor);

		init_timer(&ops->cursor_timer);
		ops->cursor_timer.function = cursor_timer_handler;
		ops->cursor_timer.expires = jiffies + HZ / 5;
		ops->cursor_timer.data = (unsigned long ) info;
		add_timer(&ops->cursor_timer);
		ops->flags |= FBCON_FLAGS_CURSOR_TIMER;
	}
}