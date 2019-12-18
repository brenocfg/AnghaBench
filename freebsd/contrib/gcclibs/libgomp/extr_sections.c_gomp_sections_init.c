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
struct gomp_work_share {int chunk_size; unsigned int end; int incr; int next; int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS_DYNAMIC ; 

__attribute__((used)) static inline void
gomp_sections_init (struct gomp_work_share *ws, unsigned count)
{
  ws->sched = GFS_DYNAMIC;
  ws->chunk_size = 1;
  ws->end = count + 1;
  ws->incr = 1;
  ws->next = 1;
}