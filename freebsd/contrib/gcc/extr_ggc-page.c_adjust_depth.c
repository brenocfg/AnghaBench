#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ context_depth; } ;
typedef  TYPE_1__ page_entry ;
struct TYPE_4__ {int by_depth_in_use; size_t depth_in_use; TYPE_1__** by_depth; } ;

/* Variables and functions */
 TYPE_2__ G ; 

__attribute__((used)) static inline void
adjust_depth (void)
{
  page_entry *top;

  if (G.by_depth_in_use)
    {
      top = G.by_depth[G.by_depth_in_use-1];

      /* Peel back indices in depth that index into by_depth, so that
	 as new elements are added to by_depth, we note the indices
	 of those elements, if they are for new context depths.  */
      while (G.depth_in_use > (size_t)top->context_depth+1)
	--G.depth_in_use;
    }
}