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
struct xenfb_info {int /*<<< orphan*/  resize_lock; scalar_t__ resize_dpy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xenfb_do_resize (struct xenfb_info*) ; 
 int /*<<< orphan*/  xenfb_queue_full (struct xenfb_info*) ; 

__attribute__((used)) static void xenfb_handle_resize_dpy(struct xenfb_info *info)
{
	unsigned long flags;

	spin_lock_irqsave(&info->resize_lock, flags);
	if (info->resize_dpy) {
		if (!xenfb_queue_full(info)) {
			info->resize_dpy = 0;
			xenfb_do_resize(info);
		}
	}
	spin_unlock_irqrestore(&info->resize_lock, flags);
}