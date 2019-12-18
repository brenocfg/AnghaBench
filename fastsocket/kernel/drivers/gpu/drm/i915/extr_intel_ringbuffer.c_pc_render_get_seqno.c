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
struct pipe_control {int /*<<< orphan*/ * cpu_page; } ;
struct intel_ring_buffer {struct pipe_control* private; } ;

/* Variables and functions */

__attribute__((used)) static u32
pc_render_get_seqno(struct intel_ring_buffer *ring, bool lazy_coherency)
{
	struct pipe_control *pc = ring->private;
	return pc->cpu_page[0];
}