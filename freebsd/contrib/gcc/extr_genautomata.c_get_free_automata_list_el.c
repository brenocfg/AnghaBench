#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct automata_list_el {int dummy; } ;
typedef  TYPE_1__* automata_list_el_t ;
struct TYPE_5__ {struct TYPE_5__* next_automata_list_el; int /*<<< orphan*/ * automaton; } ;

/* Variables and functions */
 TYPE_1__* create_node (int) ; 
 TYPE_1__* first_free_automata_list_el ; 

__attribute__((used)) static automata_list_el_t
get_free_automata_list_el (void)
{
  automata_list_el_t result;

  if (first_free_automata_list_el != NULL)
    {
      result = first_free_automata_list_el;
      first_free_automata_list_el
	= first_free_automata_list_el->next_automata_list_el;
    }
  else
    result = create_node (sizeof (struct automata_list_el));
  result->automaton = NULL;
  result->next_automata_list_el = NULL;
  return result;
}