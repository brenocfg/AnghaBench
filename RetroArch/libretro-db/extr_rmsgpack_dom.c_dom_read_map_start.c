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
typedef  unsigned int uint32_t ;
struct TYPE_3__ {unsigned int len; struct rmsgpack_dom_pair* items; } ;
struct TYPE_4__ {TYPE_1__ map; } ;
struct rmsgpack_dom_value {TYPE_2__ val; int /*<<< orphan*/  type; } ;
struct rmsgpack_dom_pair {int /*<<< orphan*/  key; int /*<<< orphan*/  value; } ;
struct dom_reader_state {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RDT_MAP ; 
 scalar_t__ calloc (unsigned int,int) ; 
 struct rmsgpack_dom_value* dom_reader_state_pop (struct dom_reader_state*) ; 
 scalar_t__ dom_reader_state_push (struct dom_reader_state*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dom_read_map_start(uint32_t len, void *data)
{
   unsigned i;
   struct rmsgpack_dom_pair *items = NULL;
   struct dom_reader_state *dom_state = (struct dom_reader_state *)data;
   struct rmsgpack_dom_value *v = dom_reader_state_pop(dom_state);

   v->type = RDT_MAP;
   v->val.map.len = len;
   v->val.map.items = NULL;

   items = (struct rmsgpack_dom_pair *)calloc(len,
         sizeof(struct rmsgpack_dom_pair));

   if (!items)
      return -ENOMEM;

   v->val.map.items = items;

   for (i = 0; i < len; i++)
   {
      if (dom_reader_state_push(dom_state, &items[i].value) < 0)
         return -ENOMEM;
      if (dom_reader_state_push(dom_state, &items[i].key) < 0)
         return -ENOMEM;
   }

   return 0;
}