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
 scalar_t__ DDR_ARE_DEPENDENT (struct data_dependence_relation*) ; 
 scalar_t__ DDR_SUBSCRIPTS (struct data_dependence_relation*) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  subscript_p ; 

void
free_dependence_relation (struct data_dependence_relation *ddr)
{
  if (ddr == NULL)
    return;

  if (DDR_ARE_DEPENDENT (ddr) == NULL_TREE && DDR_SUBSCRIPTS (ddr))
    VEC_free (subscript_p, heap, DDR_SUBSCRIPTS (ddr));

  free (ddr);
}