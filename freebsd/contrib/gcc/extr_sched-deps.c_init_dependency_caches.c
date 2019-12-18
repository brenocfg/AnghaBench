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

/* Variables and functions */
 scalar_t__ cache_size ; 
 int /*<<< orphan*/  extend_dependency_caches (int,int) ; 
 int n_basic_blocks ; 

void
init_dependency_caches (int luid)
{
  /* ?!? We could save some memory by computing a per-region luid mapping
     which could reduce both the number of vectors in the cache and the size
     of each vector.  Instead we just avoid the cache entirely unless the
     average number of instructions in a basic block is very high.  See
     the comment before the declaration of true_dependency_cache for
     what we consider "very high".  */
  if (luid / n_basic_blocks > 100 * 5)
    {
      cache_size = 0;
      extend_dependency_caches (luid, true);
    }
}