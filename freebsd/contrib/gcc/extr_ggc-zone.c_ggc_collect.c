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
struct alloc_zone {int was_collected; char* name; struct alloc_zone* next_zone; scalar_t__ allocated; scalar_t__ dead; scalar_t__ allocated_last_gc; } ;
struct TYPE_2__ {struct alloc_zone* zones; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 int GGC_DEBUG_LEVEL ; 
 int /*<<< orphan*/  GGC_MIN_EXPAND ; 
 int /*<<< orphan*/  GGC_MIN_HEAPSIZE ; 
 float MAX (float,size_t) ; 
 float PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_GC ; 
 float calculate_average_page_survival (struct alloc_zone*) ; 
 int /*<<< orphan*/  free (struct alloc_zone*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int ggc_collect_1 (struct alloc_zone*,int) ; 
 int /*<<< orphan*/  ggc_force_collect ; 
 struct alloc_zone main_zone ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  release_pages (struct alloc_zone*) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_free_marks () ; 

void
ggc_collect (void)
{
  struct alloc_zone *zone;
  bool marked = false;

  timevar_push (TV_GC);

  if (!ggc_force_collect)
    {
      float allocated_last_gc = 0, allocated = 0, min_expand;

      for (zone = G.zones; zone; zone = zone->next_zone)
	{
	  allocated_last_gc += zone->allocated_last_gc;
	  allocated += zone->allocated;
	}

      allocated_last_gc =
	MAX (allocated_last_gc,
	     (size_t) PARAM_VALUE (GGC_MIN_HEAPSIZE) * 1024);
      min_expand = allocated_last_gc * PARAM_VALUE (GGC_MIN_EXPAND) / 100;

      if (allocated < allocated_last_gc + min_expand)
	{
	  timevar_pop (TV_GC);
	  return;
	}
    }

  /* Start by possibly collecting the main zone.  */
  main_zone.was_collected = false;
  marked |= ggc_collect_1 (&main_zone, true);

  /* In order to keep the number of collections down, we don't
     collect other zones unless we are collecting the main zone.  This
     gives us roughly the same number of collections as we used to
     have with the old gc.  The number of collection is important
     because our main slowdown (according to profiling) is now in
     marking.  So if we mark twice as often as we used to, we'll be
     twice as slow.  Hopefully we'll avoid this cost when we mark
     zone-at-a-time.  */
  /* NOTE drow/2004-07-28: We now always collect the main zone, but
     keep this code in case the heuristics are further refined.  */

  if (main_zone.was_collected)
    {
      struct alloc_zone *zone;

      for (zone = main_zone.next_zone; zone; zone = zone->next_zone)
	{
	  zone->was_collected = false;
	  marked |= ggc_collect_1 (zone, !marked);
	}
    }

#ifdef GATHER_STATISTICS
  /* Print page survival stats, if someone wants them.  */
  if (GGC_DEBUG_LEVEL >= 2)
    {
      for (zone = G.zones; zone; zone = zone->next_zone)
	{
	  if (zone->was_collected)
	    {
	      float f = calculate_average_page_survival (zone);
	      printf ("Average page survival in zone `%s' is %f\n",
		      zone->name, f);
	    }
	}
    }
#endif

  if (marked)
    zone_free_marks ();

  /* Free dead zones.  */
  for (zone = G.zones; zone && zone->next_zone; zone = zone->next_zone)
    {
      if (zone->next_zone->dead)
	{
	  struct alloc_zone *dead_zone = zone->next_zone;

	  printf ("Zone `%s' is dead and will be freed.\n", dead_zone->name);

	  /* The zone must be empty.  */
	  gcc_assert (!dead_zone->allocated);

	  /* Unchain the dead zone, release all its pages and free it.  */
	  zone->next_zone = zone->next_zone->next_zone;
	  release_pages (dead_zone);
	  free (dead_zone);
	}
    }

  timevar_pop (TV_GC);
}