#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
struct TYPE_8__ {int query_units_num; int units_num; } ;
struct TYPE_7__ {scalar_t__ query_p; } ;
struct TYPE_6__ {int* presence_signature; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int* create_node (unsigned int) ; 
 TYPE_4__* description ; 
 int first_cycle_unit_presence (TYPE_1__*,int) ; 
 TYPE_2__** units_array ; 

__attribute__((used)) static void
cache_presence (state_t state)
{
  int i, num = 0;
  unsigned int sz;
  sz = (description->query_units_num + sizeof (int) * CHAR_BIT - 1)
        / (sizeof (int) * CHAR_BIT);
  
  state->presence_signature = create_node (sz * sizeof (int));
  for (i = 0; i < description->units_num; i++)
    if (units_array [i]->query_p)
      {
	int presence1_p = first_cycle_unit_presence (state, i);
	state->presence_signature[num / (sizeof (int) * CHAR_BIT)]
	  |= (!!presence1_p) << (num % (sizeof (int) * CHAR_BIT));
	num++;
      }
}