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
struct TYPE_3__ {unsigned int len; struct rmsgpack_dom_value* items; } ;
struct TYPE_4__ {TYPE_1__ array; } ;
struct rmsgpack_dom_value {TYPE_2__ val; int /*<<< orphan*/  type; } ;
struct dom_reader_state {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RDT_ARRAY ; 
 scalar_t__ calloc (unsigned int,int) ; 
 struct rmsgpack_dom_value* dom_reader_state_pop (struct dom_reader_state*) ; 
 scalar_t__ dom_reader_state_push (struct dom_reader_state*,struct rmsgpack_dom_value*) ; 

__attribute__((used)) static int dom_read_array_start(uint32_t len, void *data)
{
	unsigned i;
	struct dom_reader_state *dom_state = (struct dom_reader_state *)data;
	struct rmsgpack_dom_value *v       = dom_reader_state_pop(dom_state);
	struct rmsgpack_dom_value *items   = NULL;

	v->type = RDT_ARRAY;
	v->val.array.len = len;
	v->val.array.items = NULL;

	items = (struct rmsgpack_dom_value *)calloc(len, sizeof(*items));

	if (!items)
		return -ENOMEM;

	v->val.array.items = items;

	for (i = 0; i < len; i++)
   {
      if (dom_reader_state_push(dom_state, &items[i]) < 0)
         return -ENOMEM;
   }

	return 0;
}