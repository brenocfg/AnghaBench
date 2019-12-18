#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ggc_statistics {int dummy; } ;
typedef  int /*<<< orphan*/  stats ;
struct TYPE_6__ {size_t num_free_objects; scalar_t__ bytes; struct TYPE_6__* next; } ;
typedef  TYPE_2__ page_entry ;
struct TYPE_5__ {int /*<<< orphan*/ * total_allocated_per_order; int /*<<< orphan*/ * total_overhead_per_order; int /*<<< orphan*/  total_allocated_under128; int /*<<< orphan*/  total_overhead_under128; int /*<<< orphan*/  total_allocated_under64; int /*<<< orphan*/  total_overhead_under64; int /*<<< orphan*/  total_allocated_under32; int /*<<< orphan*/  total_overhead_under32; int /*<<< orphan*/  total_allocated; int /*<<< orphan*/  total_overhead; } ;
struct TYPE_7__ {size_t bytes_mapped; size_t allocated; TYPE_1__ stats; TYPE_2__** pages; scalar_t__ allocated_last_gc; } ;

/* Variables and functions */
 scalar_t__ BITMAP_SIZE (size_t) ; 
 TYPE_4__ G ; 
 unsigned int NUM_ORDERS ; 
 size_t OBJECTS_IN_PAGE (TYPE_2__*) ; 
 int OBJECT_SIZE (unsigned int) ; 
 int /*<<< orphan*/  SCALE (size_t) ; 
 int /*<<< orphan*/  STAT_LABEL (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ggc_print_common_statistics (int /*<<< orphan*/ ,struct ggc_statistics*) ; 
 int /*<<< orphan*/  memset (struct ggc_statistics*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_pages () ; 
 int /*<<< orphan*/  stderr ; 

void
ggc_print_statistics (void)
{
  struct ggc_statistics stats;
  unsigned int i;
  size_t total_overhead = 0;

  /* Clear the statistics.  */
  memset (&stats, 0, sizeof (stats));

  /* Make sure collection will really occur.  */
  G.allocated_last_gc = 0;

  /* Collect and print the statistics common across collectors.  */
  ggc_print_common_statistics (stderr, &stats);

  /* Release free pages so that we will not count the bytes allocated
     there as part of the total allocated memory.  */
  release_pages ();

  /* Collect some information about the various sizes of
     allocation.  */
  fprintf (stderr,
           "Memory still allocated at the end of the compilation process\n");
  fprintf (stderr, "%-5s %10s  %10s  %10s\n",
	   "Size", "Allocated", "Used", "Overhead");
  for (i = 0; i < NUM_ORDERS; ++i)
    {
      page_entry *p;
      size_t allocated;
      size_t in_use;
      size_t overhead;

      /* Skip empty entries.  */
      if (!G.pages[i])
	continue;

      overhead = allocated = in_use = 0;

      /* Figure out the total number of bytes allocated for objects of
	 this size, and how many of them are actually in use.  Also figure
	 out how much memory the page table is using.  */
      for (p = G.pages[i]; p; p = p->next)
	{
	  allocated += p->bytes;
	  in_use +=
	    (OBJECTS_IN_PAGE (p) - p->num_free_objects) * OBJECT_SIZE (i);

	  overhead += (sizeof (page_entry) - sizeof (long)
		       + BITMAP_SIZE (OBJECTS_IN_PAGE (p) + 1));
	}
      fprintf (stderr, "%-5lu %10lu%c %10lu%c %10lu%c\n",
	       (unsigned long) OBJECT_SIZE (i),
	       SCALE (allocated), STAT_LABEL (allocated),
	       SCALE (in_use), STAT_LABEL (in_use),
	       SCALE (overhead), STAT_LABEL (overhead));
      total_overhead += overhead;
    }
  fprintf (stderr, "%-5s %10lu%c %10lu%c %10lu%c\n", "Total",
	   SCALE (G.bytes_mapped), STAT_LABEL (G.bytes_mapped),
	   SCALE (G.allocated), STAT_LABEL(G.allocated),
	   SCALE (total_overhead), STAT_LABEL (total_overhead));

#ifdef GATHER_STATISTICS  
  {
    fprintf (stderr, "\nTotal allocations and overheads during the compilation process\n");

    fprintf (stderr, "Total Overhead:                        %10lld\n",
             G.stats.total_overhead);
    fprintf (stderr, "Total Allocated:                       %10lld\n",
             G.stats.total_allocated);

    fprintf (stderr, "Total Overhead  under  32B:            %10lld\n",
             G.stats.total_overhead_under32);
    fprintf (stderr, "Total Allocated under  32B:            %10lld\n",
             G.stats.total_allocated_under32);
    fprintf (stderr, "Total Overhead  under  64B:            %10lld\n",
             G.stats.total_overhead_under64);
    fprintf (stderr, "Total Allocated under  64B:            %10lld\n",
             G.stats.total_allocated_under64);
    fprintf (stderr, "Total Overhead  under 128B:            %10lld\n",
             G.stats.total_overhead_under128);
    fprintf (stderr, "Total Allocated under 128B:            %10lld\n",
             G.stats.total_allocated_under128);
   
    for (i = 0; i < NUM_ORDERS; i++)
      if (G.stats.total_allocated_per_order[i])
        {
          fprintf (stderr, "Total Overhead  page size %7d:     %10lld\n",
                   OBJECT_SIZE (i), G.stats.total_overhead_per_order[i]);
          fprintf (stderr, "Total Allocated page size %7d:     %10lld\n",
                   OBJECT_SIZE (i), G.stats.total_allocated_per_order[i]);
        }
  }
#endif
}