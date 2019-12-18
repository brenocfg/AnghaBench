#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* automata_list_el_t ;
struct TYPE_4__ {struct TYPE_4__* next_automata_list_el; } ;

/* Variables and functions */
 TYPE_1__* first_free_automata_list_el ; 

__attribute__((used)) static void
free_automata_list_el (automata_list_el_t automata_list_el)
{
  if (automata_list_el == NULL)
    return;
  automata_list_el->next_automata_list_el = first_free_automata_list_el;
  first_free_automata_list_el = automata_list_el;
}