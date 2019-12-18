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

/* Variables and functions */
 unsigned int gomp_resolve_num_threads (unsigned int) ; 
 int /*<<< orphan*/  gomp_team_start (void (*) (void*),void*,unsigned int,int /*<<< orphan*/ *) ; 

void
GOMP_parallel_start (void (*fn) (void *), void *data, unsigned num_threads)
{
  num_threads = gomp_resolve_num_threads (num_threads);
  gomp_team_start (fn, data, num_threads, NULL);
}