#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tree_stats {double total_weight; double weighted_size; int** weighted_address_bits; int /*<<< orphan*/  live_obj_count; int /*<<< orphan*/  total_size; int /*<<< orphan*/  obj_count; } ;
typedef  TYPE_1__* mfsplay_tree_node ;
struct TYPE_5__ {uintptr_t high; uintptr_t low; int liveness; scalar_t__ write_count; scalar_t__ read_count; } ;
typedef  TYPE_2__ __mf_object_t ;
struct TYPE_4__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
__mf_adapt_cache_fn (mfsplay_tree_node n, void *param)
{
  __mf_object_t *obj = (__mf_object_t *) n->value;
  struct tree_stats *s = (struct tree_stats *) param;

  assert (obj != NULL && s != NULL);

  /* Exclude never-accessed objects.  */
  if (obj->read_count + obj->write_count)
    {
      s->obj_count ++;
      s->total_size += (obj->high - obj->low + 1);

      if (obj->liveness)
        {
          unsigned i;
          uintptr_t addr;

          /* VERBOSE_TRACE ("analyze low=%p live=%u name=`%s'\n",
             (void *) obj->low, obj->liveness, obj->name); */

          s->live_obj_count ++;
          s->total_weight += (double) obj->liveness;
          s->weighted_size +=
            (double) (obj->high - obj->low + 1) *
            (double) obj->liveness;

          addr = obj->low;
          for (i=0; i<sizeof(uintptr_t) * 8; i++)
            {
              unsigned bit = addr & 1;
              s->weighted_address_bits[i][bit] += obj->liveness;
              addr = addr >> 1;
            }

          /* Age the liveness value.  */
          obj->liveness >>= 1;
        }
    }

  return 0;
}