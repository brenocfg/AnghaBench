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
typedef  TYPE_1__* state_t ;
struct TYPE_4__ {scalar_t__ automaton; int /*<<< orphan*/  reservs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int reserv_sets_are_intersected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intersected_state_reservs_p (state_t state1, state_t state2)
{
  gcc_assert (state1->automaton == state2->automaton);
  return reserv_sets_are_intersected (state1->reservs, state2->reservs);
}