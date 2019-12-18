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
struct intel_ring_buffer {int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  name; int /*<<< orphan*/  (* get_seqno ) (struct intel_ring_buffer*,int) ;int /*<<< orphan*/  request_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_last_seqno (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  stub1 (struct intel_ring_buffer*,int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool i915_hangcheck_ring_idle(struct intel_ring_buffer *ring, bool *err)
{
	if (list_empty(&ring->request_list) ||
	    i915_seqno_passed(ring->get_seqno(ring, false),
			      ring_last_seqno(ring))) {
		/* Issue a wake-up to catch stuck h/w. */
		if (waitqueue_active(&ring->irq_queue)) {
			DRM_ERROR("Hangcheck timer elapsed... %s idle\n",
				  ring->name);
			wake_up_all(&ring->irq_queue);
			*err = true;
		}
		return true;
	}
	return false;
}