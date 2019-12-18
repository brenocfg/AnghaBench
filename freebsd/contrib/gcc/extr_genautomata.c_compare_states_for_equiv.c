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
typedef  TYPE_1__* state_t ;
struct TYPE_4__ {int query_units_num; } ;
struct TYPE_3__ {scalar_t__ num_out_arcs; scalar_t__* presence_signature; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 TYPE_2__* description ; 

__attribute__((used)) static int
compare_states_for_equiv (const void *state_ptr_1,
			  const void *state_ptr_2)
{
  state_t s1 = *(state_t *)state_ptr_1;
  state_t s2 = *(state_t *)state_ptr_2;
  unsigned int sz, si;
  if (s1->num_out_arcs < s2->num_out_arcs)
    return -1;
  else if (s1->num_out_arcs > s2->num_out_arcs)
    return 1;

  sz = (description->query_units_num + sizeof (int) * CHAR_BIT - 1)
	/ (sizeof (int) * CHAR_BIT);

  for (si = 0; si < sz; si++)
    if (s1->presence_signature[si] < s2->presence_signature[si])
      return -1;
    else if (s1->presence_signature[si] > s2->presence_signature[si])
      return 1;
  return 0;
}