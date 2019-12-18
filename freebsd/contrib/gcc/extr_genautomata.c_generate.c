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
struct TYPE_2__ {scalar_t__ units_num; } ;

/* Variables and functions */
 scalar_t__ automata_num ; 
 int /*<<< orphan*/  automaton_generation_time ; 
 int /*<<< orphan*/  create_automata () ; 
 int /*<<< orphan*/  create_ticker () ; 
 TYPE_1__* description ; 
 int /*<<< orphan*/  initiate_arcs () ; 
 int /*<<< orphan*/  initiate_automata_lists () ; 
 int /*<<< orphan*/  initiate_excl_sets () ; 
 int /*<<< orphan*/  initiate_pass_states () ; 
 int /*<<< orphan*/  initiate_presence_absence_pattern_sets () ; 
 int /*<<< orphan*/  initiate_states () ; 
 scalar_t__ split_argument ; 
 int /*<<< orphan*/  ticker_off (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate (void)
{
  automata_num = split_argument;
  if (description->units_num < automata_num)
    automata_num = description->units_num;
  initiate_states ();
  initiate_arcs ();
  initiate_automata_lists ();
  initiate_pass_states ();
  initiate_excl_sets ();
  initiate_presence_absence_pattern_sets ();
  automaton_generation_time = create_ticker ();
  create_automata ();
  ticker_off (&automaton_generation_time);
}