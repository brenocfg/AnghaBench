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
typedef  TYPE_1__* automaton_t ;
struct TYPE_4__ {scalar_t__ achieved_states_num; } ;

/* Variables and functions */
 scalar_t__ curr_state_order_num ; 
 int /*<<< orphan*/  pass_states (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_order_state_num ; 

__attribute__((used)) static void
enumerate_states (automaton_t automaton)
{
  curr_state_order_num = 0;
  pass_states (automaton, set_order_state_num);
  automaton->achieved_states_num = curr_state_order_num;
}