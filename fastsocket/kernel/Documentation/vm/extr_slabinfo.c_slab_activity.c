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
struct slabinfo {unsigned long alloc_fastpath; unsigned long free_fastpath; unsigned long alloc_slowpath; unsigned long free_slowpath; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long slab_activity(struct slabinfo *s)
{
	return 	s->alloc_fastpath + s->free_fastpath +
		s->alloc_slowpath + s->free_slowpath;
}