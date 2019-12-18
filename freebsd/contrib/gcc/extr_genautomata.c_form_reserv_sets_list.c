#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pattern_reserv {int dummy; } ;
typedef  TYPE_2__* pattern_set_el_t ;
typedef  TYPE_3__* pattern_reserv_t ;
struct TYPE_9__ {struct TYPE_9__* next_pattern_reserv; int /*<<< orphan*/  reserv; } ;
struct TYPE_8__ {int units_num; TYPE_1__** unit_decls; struct TYPE_8__* next_pattern_set_el; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_set_p; int /*<<< orphan*/  unit_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  alloc_empty_reserv_sets () ; 
 TYPE_3__* create_node (int) ; 

__attribute__((used)) static pattern_reserv_t
form_reserv_sets_list (pattern_set_el_t pattern_list)
{
  pattern_set_el_t el;
  pattern_reserv_t first, curr, prev;
  int i;

  prev = first = NULL;
  for (el = pattern_list; el != NULL; el = el->next_pattern_set_el)
    {
      curr = create_node (sizeof (struct pattern_reserv));
      curr->reserv = alloc_empty_reserv_sets ();
      curr->next_pattern_reserv = NULL;
      for (i = 0; i < el->units_num; i++)
	{
	  SET_BIT (curr->reserv, el->unit_decls [i]->unit_num);
	  el->unit_decls [i]->in_set_p = TRUE;
	}
      if (prev != NULL)
	prev->next_pattern_reserv = curr;
      else
	first = curr;
      prev = curr;
    }
  return first;
}