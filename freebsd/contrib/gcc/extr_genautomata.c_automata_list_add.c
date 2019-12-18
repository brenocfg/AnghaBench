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
typedef  int /*<<< orphan*/  automaton_t ;
typedef  TYPE_1__* automata_list_el_t ;
struct TYPE_4__ {struct TYPE_4__* next_automata_list_el; int /*<<< orphan*/  automaton; } ;

/* Variables and functions */
 TYPE_1__* current_automata_list ; 
 TYPE_1__* get_free_automata_list_el () ; 

__attribute__((used)) static void
automata_list_add (automaton_t automaton)
{
  automata_list_el_t el;

  el = get_free_automata_list_el ();
  el->automaton = automaton;
  el->next_automata_list_el = current_automata_list;
  current_automata_list = el;
}