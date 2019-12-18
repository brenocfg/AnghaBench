#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reserv_sets_t ;
typedef  TYPE_1__* automaton_t ;
struct TYPE_7__ {int units_num; } ;
struct TYPE_6__ {scalar_t__ automaton_decl; int min_occ_cycle_num; scalar_t__ in_set_p; scalar_t__ query_p; } ;
struct TYPE_5__ {scalar_t__ corresponding_automaton_decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_empty_reserv_sets () ; 
 TYPE_4__* description ; 
 int max_cycles_num ; 
 int /*<<< orphan*/  set_unit_reserv (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__** units_array ; 

__attribute__((used)) static reserv_sets_t
form_reservs_matter (automaton_t automaton)
{
  int cycle, unit;
  reserv_sets_t reservs_matter = alloc_empty_reserv_sets();

  for (cycle = 0; cycle < max_cycles_num; cycle++)
    for (unit = 0; unit < description->units_num; unit++)
      if (units_array [unit]->automaton_decl
	  == automaton->corresponding_automaton_decl
	  && (cycle >= units_array [unit]->min_occ_cycle_num
	      /* We can not remove queried unit from reservations.  */
	      || units_array [unit]->query_p
	      /* We can not remove units which are used
		 `exclusion_set', `presence_set',
		 `final_presence_set', `absence_set', and
		 `final_absence_set'.  */
	      || units_array [unit]->in_set_p))
	set_unit_reserv (reservs_matter, cycle, unit);
  return reservs_matter;
}