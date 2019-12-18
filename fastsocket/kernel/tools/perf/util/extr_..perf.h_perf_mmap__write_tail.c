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
struct perf_mmap {struct perf_event_mmap_page* base; } ;
struct perf_event_mmap_page {unsigned long data_tail; } ;

/* Variables and functions */

__attribute__((used)) static inline void perf_mmap__write_tail(struct perf_mmap *md,
					 unsigned long tail)
{
	struct perf_event_mmap_page *pc = md->base;

	/*
	 * ensure all reads are done before we write the tail out.
	 */
	/* mb(); */
	pc->data_tail = tail;
}