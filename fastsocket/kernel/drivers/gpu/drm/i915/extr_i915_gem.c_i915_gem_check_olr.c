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
typedef  scalar_t__ u32 ;
struct intel_ring_buffer {scalar_t__ outstanding_lazy_request; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int i915_add_request (struct intel_ring_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i915_gem_check_olr(struct intel_ring_buffer *ring, u32 seqno)
{
	int ret;

	BUG_ON(!mutex_is_locked(&ring->dev->struct_mutex));

	ret = 0;
	if (seqno == ring->outstanding_lazy_request)
		ret = i915_add_request(ring, NULL, NULL);

	return ret;
}