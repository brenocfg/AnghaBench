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
struct dom_info {size_t* set_chain; scalar_t__* key; size_t* path_min; } ;
typedef  size_t TBB ;

/* Variables and functions */

__attribute__((used)) static void
compress (struct dom_info *di, TBB v)
{
  /* Btw. It's not worth to unrecurse compress() as the depth is usually not
     greater than 5 even for huge graphs (I've not seen call depth > 4).
     Also performance wise compress() ranges _far_ behind eval().  */
  TBB parent = di->set_chain[v];
  if (di->set_chain[parent])
    {
      compress (di, parent);
      if (di->key[di->path_min[parent]] < di->key[di->path_min[v]])
	di->path_min[v] = di->path_min[parent];
      di->set_chain[v] = di->set_chain[parent];
    }
}