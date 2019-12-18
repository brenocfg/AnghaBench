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
struct gomp_work_share {int dummy; } ;
typedef  enum gomp_schedule_type { ____Placeholder_gomp_schedule_type } gomp_schedule_type ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_loop_init (struct gomp_work_share*,long,long,long,int,long) ; 
 struct gomp_work_share* gomp_new_work_share (int,unsigned int) ; 
 unsigned int gomp_resolve_num_threads (unsigned int) ; 
 int /*<<< orphan*/  gomp_team_start (void (*) (void*),void*,unsigned int,struct gomp_work_share*) ; 

__attribute__((used)) static void
gomp_parallel_loop_start (void (*fn) (void *), void *data,
			  unsigned num_threads, long start, long end,
			  long incr, enum gomp_schedule_type sched,
			  long chunk_size)
{
  struct gomp_work_share *ws;

  num_threads = gomp_resolve_num_threads (num_threads);
  ws = gomp_new_work_share (false, num_threads);
  gomp_loop_init (ws, start, end, incr, sched, chunk_size);
  gomp_team_start (fn, data, num_threads, ws);
}