#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * vars; int /*<<< orphan*/ * regs; } ;
typedef  TYPE_1__ dataflow_set ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  attrs_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dataflow_set_destroy (dataflow_set *set)
{
  int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    attrs_list_clear (&set->regs[i]);

  htab_delete (set->vars);
  set->vars = NULL;
}