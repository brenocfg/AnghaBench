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

/* Variables and functions */
 scalar_t__ gomp_dyn_var ; 
 struct gomp_work_share* gomp_new_work_share (int,unsigned int) ; 
 unsigned int gomp_resolve_num_threads (unsigned int) ; 
 int /*<<< orphan*/  gomp_sections_init (struct gomp_work_share*,unsigned int) ; 
 int /*<<< orphan*/  gomp_team_start (void (*) (void*),void*,unsigned int,struct gomp_work_share*) ; 

void
GOMP_parallel_sections_start (void (*fn) (void *), void *data,
			      unsigned num_threads, unsigned count)
{
  struct gomp_work_share *ws;

  num_threads = gomp_resolve_num_threads (num_threads);
  if (gomp_dyn_var && num_threads > count)
    num_threads = count;

  ws = gomp_new_work_share (false, num_threads);
  gomp_sections_init (ws, count);
  gomp_team_start (fn, data, num_threads, ws);
}