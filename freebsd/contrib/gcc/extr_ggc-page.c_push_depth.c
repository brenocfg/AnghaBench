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
struct TYPE_2__ {int depth_in_use; int depth_max; unsigned int* depth; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 unsigned int* xrealloc (unsigned int*,int) ; 

__attribute__((used)) inline static void
push_depth (unsigned int i)
{
  if (G.depth_in_use >= G.depth_max)
    {
      G.depth_max *= 2;
      G.depth = xrealloc (G.depth, G.depth_max * sizeof (unsigned int));
    }
  G.depth[G.depth_in_use++] = i;
}