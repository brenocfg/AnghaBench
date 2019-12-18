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
 int /*<<< orphan*/ * XRESIZEVEC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * anti_dependency_cache ; 
 int /*<<< orphan*/  bitmap_head ; 
 int /*<<< orphan*/  bitmap_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cache_size ; 
 TYPE_1__* current_sched_info ; 
 int /*<<< orphan*/ * forward_dependency_cache ; 
 int /*<<< orphan*/ * output_dependency_cache ; 
 int /*<<< orphan*/ * spec_dependency_cache ; 
 int /*<<< orphan*/ * true_dependency_cache ; 

void
extend_dependency_caches (int n, bool create_p)
{
  if (create_p || true_dependency_cache)
    {
      int i, luid = cache_size + n;

      true_dependency_cache = XRESIZEVEC (bitmap_head, true_dependency_cache,
					  luid);
      output_dependency_cache = XRESIZEVEC (bitmap_head,
					    output_dependency_cache, luid);
      anti_dependency_cache = XRESIZEVEC (bitmap_head, anti_dependency_cache,
					  luid);
#ifdef ENABLE_CHECKING
      forward_dependency_cache = XRESIZEVEC (bitmap_head,
					     forward_dependency_cache, luid);
#endif
      if (current_sched_info->flags & DO_SPECULATION)
        spec_dependency_cache = XRESIZEVEC (bitmap_head, spec_dependency_cache,
					    luid);

      for (i = cache_size; i < luid; i++)
	{
	  bitmap_initialize (&true_dependency_cache[i], 0);
	  bitmap_initialize (&output_dependency_cache[i], 0);
	  bitmap_initialize (&anti_dependency_cache[i], 0);
#ifdef ENABLE_CHECKING
	  bitmap_initialize (&forward_dependency_cache[i], 0);
#endif
          if (current_sched_info->flags & DO_SPECULATION)
            bitmap_initialize (&spec_dependency_cache[i], 0);
	}
      cache_size = luid;
    }
}