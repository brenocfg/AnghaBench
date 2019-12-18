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
struct __mf_cache {uintptr_t low; uintptr_t high; } ;
struct TYPE_3__ {uintptr_t low; uintptr_t high; scalar_t__ write_count; scalar_t__ read_count; } ;
typedef  TYPE_1__ __mf_object_t ;

/* Variables and functions */
 scalar_t__ LIKELY (scalar_t__) ; 
 uintptr_t MAXPTR ; 
 uintptr_t MINPTR ; 
 unsigned int __mf_lc_mask ; 
 struct __mf_cache* __mf_lookup_cache ; 

__attribute__((used)) static void
__mf_uncache_object (__mf_object_t *old_obj)
{
  /* Remove any low/high pointers for this object from the lookup cache.  */

  /* Can it possibly exist in the cache?  */
  if (LIKELY (old_obj->read_count + old_obj->write_count))
    {
      /* As reported by Herman ten Brugge, we need to scan the entire
         cache for entries that may hit this object. */
      uintptr_t low = old_obj->low;
      uintptr_t high = old_obj->high;
      struct __mf_cache *entry = & __mf_lookup_cache [0];
      unsigned i;
      for (i = 0; i <= __mf_lc_mask; i++, entry++)
        {
          /* NB: the "||" in the following test permits this code to
             tolerate the situation introduced by __mf_check over
             contiguous objects, where a cache entry spans several
             objects.  */
          if (entry->low == low || entry->high == high)
            {
              entry->low = MAXPTR;
              entry->high = MINPTR;
            }
        }
    }
}