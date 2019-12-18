#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int len; TYPE_3__* items; } ;
struct TYPE_5__ {TYPE_1__ map; } ;
struct rmsgpack_dom_value {scalar_t__ type; TYPE_2__ val; } ;
struct TYPE_6__ {struct rmsgpack_dom_value value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ RDT_MAP ; 
 scalar_t__ rmsgpack_dom_value_cmp (struct rmsgpack_dom_value const*,int /*<<< orphan*/ *) ; 

struct rmsgpack_dom_value *rmsgpack_dom_value_map_value(
      const struct rmsgpack_dom_value *map,
      const struct rmsgpack_dom_value *key)
{
   unsigned i;
   if (map->type != RDT_MAP)
      return NULL;

   for (i = 0; i < map->val.map.len; i++)
   {
      if (rmsgpack_dom_value_cmp(key, &map->val.map.items[i].key) == 0)
         return &map->val.map.items[i].value;
   }
   return NULL;
}