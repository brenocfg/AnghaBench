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
struct data_dependence_relation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDR_A (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_B (struct data_dependence_relation*) ; 
 unsigned int DDR_NUM_SUBSCRIPTS (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DR_ACCESS_FN (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  eq_evolutions_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
same_access_functions (struct data_dependence_relation *ddr)
{
  unsigned i;

  for (i = 0; i < DDR_NUM_SUBSCRIPTS (ddr); i++)
    if (!eq_evolutions_p (DR_ACCESS_FN (DDR_A (ddr), i),
			  DR_ACCESS_FN (DDR_B (ddr), i)))
      return false;

  return true;
}