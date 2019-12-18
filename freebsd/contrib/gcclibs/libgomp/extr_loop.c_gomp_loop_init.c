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
struct gomp_work_share {int sched; long chunk_size; long end; long incr; long next; } ;
typedef  enum gomp_schedule_type { ____Placeholder_gomp_schedule_type } gomp_schedule_type ;

/* Variables and functions */

__attribute__((used)) static inline void
gomp_loop_init (struct gomp_work_share *ws, long start, long end, long incr,
		enum gomp_schedule_type sched, long chunk_size)
{
  ws->sched = sched;
  ws->chunk_size = chunk_size;
  /* Canonicalize loops that have zero iterations to ->next == ->end.  */
  ws->end = ((incr > 0 && start > end) || (incr < 0 && start < end))
	    ? start : end;
  ws->incr = incr;
  ws->next = start;
}