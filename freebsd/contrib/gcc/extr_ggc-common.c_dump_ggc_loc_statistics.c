#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct loc_descriptor {int allocated; double freed; double collected; int overhead; char* file; int line; char* function; scalar_t__ times; } ;
struct TYPE_3__ {int /*<<< orphan*/  n_elements; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_statistics ; 
 int /*<<< orphan*/  cmp_statistic ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ggc_collect () ; 
 int ggc_force_collect ; 
 int /*<<< orphan*/  htab_traverse (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 struct loc_descriptor** loc_array ; 
 TYPE_1__* loc_hash ; 
 int /*<<< orphan*/  qsort (struct loc_descriptor**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strstr (char const*,char*) ; 
 struct loc_descriptor** xcalloc (int,int /*<<< orphan*/ ) ; 

void
dump_ggc_loc_statistics (void)
{
#ifdef GATHER_STATISTICS
  int nentries = 0;
  char s[4096];
  size_t collected = 0, freed = 0, allocated = 0, overhead = 0, times = 0;
  int i;

  ggc_force_collect = true;
  ggc_collect ();

  loc_array = xcalloc (sizeof (*loc_array), loc_hash->n_elements);
  fprintf (stderr, "-------------------------------------------------------\n");
  fprintf (stderr, "\n%-48s %10s       %10s       %10s       %10s       %10s\n",
	   "source location", "Garbage", "Freed", "Leak", "Overhead", "Times");
  fprintf (stderr, "-------------------------------------------------------\n");
  htab_traverse (loc_hash, add_statistics, &nentries);
  qsort (loc_array, nentries, sizeof (*loc_array), cmp_statistic);
  for (i = 0; i < nentries; i++)
    {
      struct loc_descriptor *d = loc_array[i];
      allocated += d->allocated;
      times += d->times;
      freed += d->freed;
      collected += d->collected;
      overhead += d->overhead;
    }
  for (i = 0; i < nentries; i++)
    {
      struct loc_descriptor *d = loc_array[i];
      if (d->allocated)
	{
	  const char *s1 = d->file;
	  const char *s2;
	  while ((s2 = strstr (s1, "gcc/")))
	    s1 = s2 + 4;
	  sprintf (s, "%s:%i (%s)", s1, d->line, d->function);
	  s[48] = 0;
	  fprintf (stderr, "%-48s %10li:%4.1f%% %10li:%4.1f%% %10li:%4.1f%% %10li:%4.1f%% %10li\n", s,
		   (long)d->collected,
		   (d->collected) * 100.0 / collected,
		   (long)d->freed,
		   (d->freed) * 100.0 / freed,
		   (long)(d->allocated + d->overhead - d->freed - d->collected),
		   (d->allocated + d->overhead - d->freed - d->collected) * 100.0
		   / (allocated + overhead - freed - collected),
		   (long)d->overhead,
		   d->overhead * 100.0 / overhead,
		   (long)d->times);
	}
    }
  fprintf (stderr, "%-48s %10ld       %10ld       %10ld       %10ld       %10ld\n",
	   "Total", (long)collected, (long)freed,
	   (long)(allocated + overhead - freed - collected), (long)overhead,
	   (long)times);
  fprintf (stderr, "%-48s %10s       %10s       %10s       %10s       %10s\n",
	   "source location", "Garbage", "Freed", "Leak", "Overhead", "Times");
  fprintf (stderr, "-------------------------------------------------------\n");
#endif
}