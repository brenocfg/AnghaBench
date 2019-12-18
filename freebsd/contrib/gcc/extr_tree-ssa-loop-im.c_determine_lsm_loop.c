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
struct mem_ref {int dummy; } ;
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_more_ref_vops (struct mem_ref*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mem_refs (struct mem_ref*) ; 
 struct mem_ref* gather_mem_refs (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_loop_exit_edges (struct loop*,unsigned int*) ; 
 int /*<<< orphan*/  hoist_memory_references (struct loop*,struct mem_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  loop_suitable_for_sm (struct loop*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
determine_lsm_loop (struct loop *loop)
{
  unsigned n_exits;
  edge *exits = get_loop_exit_edges (loop, &n_exits);
  bitmap clobbered_vops;
  struct mem_ref *mem_refs;

  if (!loop_suitable_for_sm (loop, exits, n_exits))
    {
      free (exits);
      return;
    }

  /* Find the memory references in LOOP.  */
  clobbered_vops = BITMAP_ALLOC (NULL);
  mem_refs = gather_mem_refs (loop, clobbered_vops);

  /* Find the vops that are used for more than one reference.  */
  find_more_ref_vops (mem_refs, clobbered_vops);

  /* Hoist all suitable memory references.  */
  hoist_memory_references (loop, mem_refs, clobbered_vops, exits, n_exits);

  free_mem_refs (mem_refs);
  free (exits);
  BITMAP_FREE (clobbered_vops);
}