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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int DO_SPECULATION ; 
 int /*<<< orphan*/ * anti_dependency_cache ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ *) ; 
 int cache_size ; 
 TYPE_1__* current_sched_info ; 
 int /*<<< orphan*/ * forward_dependency_cache ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * output_dependency_cache ; 
 int /*<<< orphan*/ * spec_dependency_cache ; 
 int /*<<< orphan*/ * true_dependency_cache ; 

void
free_dependency_caches (void)
{
  if (true_dependency_cache)
    {
      int i;

      for (i = 0; i < cache_size; i++)
	{
	  bitmap_clear (&true_dependency_cache[i]);
	  bitmap_clear (&output_dependency_cache[i]);
	  bitmap_clear (&anti_dependency_cache[i]);
#ifdef ENABLE_CHECKING
	  bitmap_clear (&forward_dependency_cache[i]);
#endif
          if (current_sched_info->flags & DO_SPECULATION)
            bitmap_clear (&spec_dependency_cache[i]);
	}
      free (true_dependency_cache);
      true_dependency_cache = NULL;
      free (output_dependency_cache);
      output_dependency_cache = NULL;
      free (anti_dependency_cache);
      anti_dependency_cache = NULL;
#ifdef ENABLE_CHECKING
      free (forward_dependency_cache);
      forward_dependency_cache = NULL;
#endif
      if (current_sched_info->flags & DO_SPECULATION)
        {
          free (spec_dependency_cache);
          spec_dependency_cache = NULL;
        }
    }
}