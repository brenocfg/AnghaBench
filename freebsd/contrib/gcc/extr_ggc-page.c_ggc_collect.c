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
struct TYPE_2__ {float allocated_last_gc; float allocated; unsigned long context_depth_collections; int context_depth; int /*<<< orphan*/  debug_file; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 int GGC_DEBUG_LEVEL ; 
 int /*<<< orphan*/  GGC_MIN_EXPAND ; 
 int /*<<< orphan*/  GGC_MIN_HEAPSIZE ; 
 float MAX (float,size_t) ; 
 float PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_GC ; 
 int /*<<< orphan*/  clear_marks () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ggc_force_collect ; 
 int /*<<< orphan*/  ggc_mark_roots () ; 
 int /*<<< orphan*/  ggc_prune_overhead_list () ; 
 int /*<<< orphan*/  poison_pages () ; 
 int /*<<< orphan*/  quiet_flag ; 
 int /*<<< orphan*/  release_pages () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sweep_pages () ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_free_objects () ; 

void
ggc_collect (void)
{
  /* Avoid frequent unnecessary work by skipping collection if the
     total allocations haven't expanded much since the last
     collection.  */
  float allocated_last_gc =
    MAX (G.allocated_last_gc, (size_t)PARAM_VALUE (GGC_MIN_HEAPSIZE) * 1024);

  float min_expand = allocated_last_gc * PARAM_VALUE (GGC_MIN_EXPAND) / 100;

  if (G.allocated < allocated_last_gc + min_expand && !ggc_force_collect)
    return;

  timevar_push (TV_GC);
  if (!quiet_flag)
    fprintf (stderr, " {GC %luk -> ", (unsigned long) G.allocated / 1024);
  if (GGC_DEBUG_LEVEL >= 2)
    fprintf (G.debug_file, "BEGIN COLLECTING\n");

  /* Zero the total allocated bytes.  This will be recalculated in the
     sweep phase.  */
  G.allocated = 0;

  /* Release the pages we freed the last time we collected, but didn't
     reuse in the interim.  */
  release_pages ();

  /* Indicate that we've seen collections at this context depth.  */
  G.context_depth_collections = ((unsigned long)1 << (G.context_depth + 1)) - 1;

  clear_marks ();
  ggc_mark_roots ();
#ifdef GATHER_STATISTICS
  ggc_prune_overhead_list ();
#endif
  poison_pages ();
  validate_free_objects ();
  sweep_pages ();

  G.allocated_last_gc = G.allocated;

  timevar_pop (TV_GC);

  if (!quiet_flag)
    fprintf (stderr, "%luk}", (unsigned long) G.allocated / 1024);
  if (GGC_DEBUG_LEVEL >= 2)
    fprintf (G.debug_file, "END COLLECTING\n");
}