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
struct mem_ref {struct mem_ref* next; } ;
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  determine_lsm_ref (struct loop*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,struct mem_ref*) ; 

__attribute__((used)) static void
hoist_memory_references (struct loop *loop, struct mem_ref *mem_refs,
			 bitmap clobbered_vops, edge *exits, unsigned n_exits)
{
  struct mem_ref *ref;

  for (ref = mem_refs; ref; ref = ref->next)
    determine_lsm_ref (loop, exits, n_exits, clobbered_vops, ref);
}