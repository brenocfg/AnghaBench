#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* automata_list_el_t ;
struct TYPE_2__ {scalar_t__ automaton; struct TYPE_2__* next_automata_list_el; } ;

/* Variables and functions */

__attribute__((used)) static int
automata_list_eq_p (const void *automata_list_1, const void *automata_list_2)
{
  automata_list_el_t automata_list_el_1;
  automata_list_el_t automata_list_el_2;

  for (automata_list_el_1 = (automata_list_el_t) automata_list_1,
	 automata_list_el_2 = (automata_list_el_t) automata_list_2;
       automata_list_el_1 != NULL && automata_list_el_2 != NULL;
       automata_list_el_1 = automata_list_el_1->next_automata_list_el,
	 automata_list_el_2 = automata_list_el_2->next_automata_list_el)
    if (automata_list_el_1->automaton != automata_list_el_2->automaton)
      return 0;
  return automata_list_el_1 == automata_list_el_2;
}