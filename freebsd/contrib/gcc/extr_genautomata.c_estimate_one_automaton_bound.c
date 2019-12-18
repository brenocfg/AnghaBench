#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_7__ {scalar_t__ min_occ_cycle_num; scalar_t__ max_occ_cycle_num; } ;
struct TYPE_6__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_5__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_3__* DECL_UNIT (TYPE_1__*) ; 
 double MAX_FLOATING_POINT_VALUE_FOR_AUTOMATON_BOUND ; 
 int automata_num ; 
 TYPE_2__* description ; 
 scalar_t__ dm_unit ; 
 double exp (int) ; 
 int log (scalar_t__) ; 

__attribute__((used)) static double
estimate_one_automaton_bound (void)
{
  decl_t decl;
  double one_automaton_estimation_bound;
  double root_value;
  int i;

  one_automaton_estimation_bound = 1.0;
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_unit)
	{
	  root_value = exp (log (DECL_UNIT (decl)->max_occ_cycle_num
				 - DECL_UNIT (decl)->min_occ_cycle_num + 1.0)
                            / automata_num);
	  if (MAX_FLOATING_POINT_VALUE_FOR_AUTOMATON_BOUND / root_value
	      > one_automaton_estimation_bound)
	    one_automaton_estimation_bound *= root_value;
	}
    }
  return one_automaton_estimation_bound;
}