#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * reserv_sets_t ;

/* Variables and functions */
 int els_in_cycle_reserv ; 
 int els_in_reservs ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
reserv_sets_shift (reserv_sets_t result, reserv_sets_t operand)
{
  int i;

  gcc_assert (result && operand && result != operand);
  for (i = els_in_cycle_reserv; i < els_in_reservs; i++)
    result [i - els_in_cycle_reserv] = operand [i];
}