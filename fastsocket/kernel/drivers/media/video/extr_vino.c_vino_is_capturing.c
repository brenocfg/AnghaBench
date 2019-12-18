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
struct vino_channel_settings {int capturing; int /*<<< orphan*/  capture_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int vino_is_capturing(struct vino_channel_settings *vcs)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&vcs->capture_lock, flags);

	ret = vcs->capturing;

	spin_unlock_irqrestore(&vcs->capture_lock, flags);

	return ret;
}