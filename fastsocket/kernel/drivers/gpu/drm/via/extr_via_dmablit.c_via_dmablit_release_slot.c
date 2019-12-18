#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  busy_queue; int /*<<< orphan*/  blit_lock; int /*<<< orphan*/  num_free; } ;
typedef  TYPE_1__ drm_via_blitq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WAKEUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
via_dmablit_release_slot(drm_via_blitq_t *blitq)
{
	unsigned long irqsave;

	spin_lock_irqsave(&blitq->blit_lock, irqsave);
	blitq->num_free++;
	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);
	DRM_WAKEUP(&blitq->busy_queue);
}