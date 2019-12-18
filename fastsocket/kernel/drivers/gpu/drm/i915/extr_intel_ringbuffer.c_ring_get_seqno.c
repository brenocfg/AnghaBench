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
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GEM_HWS_INDEX ; 
 int /*<<< orphan*/  intel_read_status_page (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
ring_get_seqno(struct intel_ring_buffer *ring, bool lazy_coherency)
{
	return intel_read_status_page(ring, I915_GEM_HWS_INDEX);
}