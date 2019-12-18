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
struct ttm_buffer_object {int /*<<< orphan*/  event_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_is_reserved (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ttm_bo_wait_unreserved(struct ttm_buffer_object *bo,
				  bool interruptible)
{
	if (interruptible) {
		return wait_event_interruptible(bo->event_queue,
					       !ttm_bo_is_reserved(bo));
	} else {
		wait_event(bo->event_queue, !ttm_bo_is_reserved(bo));
		return 0;
	}
}