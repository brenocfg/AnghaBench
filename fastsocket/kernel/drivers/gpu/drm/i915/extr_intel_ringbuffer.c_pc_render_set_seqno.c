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

__attribute__((used)) static void
pc_render_set_seqno(struct intel_ring_buffer *ring, u32 seqno)
{
	struct pipe_control *pc = ring->private;
	pc->cpu_page[0] = seqno;
}