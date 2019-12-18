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
typedef  unsigned long page_entry ;
struct TYPE_2__ {size_t by_depth_in_use; size_t by_depth_max; unsigned long** by_depth; unsigned long** save_in_use; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 void* xrealloc (unsigned long**,int) ; 

__attribute__((used)) inline static void
push_by_depth (page_entry *p, unsigned long *s)
{
  if (G.by_depth_in_use >= G.by_depth_max)
    {
      G.by_depth_max *= 2;
      G.by_depth = xrealloc (G.by_depth,
			     G.by_depth_max * sizeof (page_entry *));
      G.save_in_use = xrealloc (G.save_in_use,
				G.by_depth_max * sizeof (unsigned long *));
    }
  G.by_depth[G.by_depth_in_use] = p;
  G.save_in_use[G.by_depth_in_use++] = s;
}