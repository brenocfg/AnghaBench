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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * page_addr; } ;
struct intel_ring_buffer {TYPE_1__ status_page; } ;

/* Variables and functions */

__attribute__((used)) static inline void
intel_write_status_page(struct intel_ring_buffer *ring,
			int reg, u32 value)
{
	ring->status_page.page_addr[reg] = value;
}