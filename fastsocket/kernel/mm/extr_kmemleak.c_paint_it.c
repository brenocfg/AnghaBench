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
struct kmemleak_object {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __paint_it (struct kmemleak_object*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void paint_it(struct kmemleak_object *object, int color)
{
	unsigned long flags;

	spin_lock_irqsave(&object->lock, flags);
	__paint_it(object, color);
	spin_unlock_irqrestore(&object->lock, flags);
}