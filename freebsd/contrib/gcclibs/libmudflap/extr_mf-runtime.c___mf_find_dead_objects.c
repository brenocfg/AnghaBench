#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {uintptr_t low; uintptr_t high; } ;
typedef  TYPE_1__ __mf_object_t ;
struct TYPE_6__ {unsigned int persistent_count; } ;

/* Variables and functions */
 unsigned int __MF_TYPE_MAX_CEM ; 
 TYPE_1__*** __mf_object_cemetary ; 
 unsigned int* __mf_object_dead_head ; 
 TYPE_2__ __mf_opts ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static unsigned
__mf_find_dead_objects (uintptr_t low, uintptr_t high,
                        __mf_object_t **objs, unsigned max_objs)
{
  if (__mf_opts.persistent_count > 0)
    {
      unsigned count = 0;
      unsigned recollection = 0;
      unsigned row = 0;

      assert (low <= high);
      assert (max_objs == 0 || objs != NULL);

      /* Widen the search from the most recent plots in each row, looking
         backward in time.  */
      recollection = 0;
      while (recollection < __mf_opts.persistent_count)
        {
          count = 0;

          for (row = 0; row <= __MF_TYPE_MAX_CEM; row ++)
            {
              unsigned plot;
              unsigned i;

              plot = __mf_object_dead_head [row];
              for (i = 0; i <= recollection; i ++)
                {
                  __mf_object_t *obj;

                  /* Look backward through row: it's a circular buffer.  */
                  if (plot > 0) plot --;
                  else plot = __mf_opts.persistent_count - 1;

                  obj = __mf_object_cemetary [row][plot];
                  if (obj && obj->low <= high && obj->high >= low)
                    {
                      /* Found an overlapping dead object!  */
                      if (count < max_objs)
                        objs [count] = obj;
                      count ++;
                    }
                }
            }

          if (count)
            break;

          /* Look farther back in time.  */
          recollection = (recollection * 2) + 1;
        }

      return count;
    } else {
      return 0;
    }
}