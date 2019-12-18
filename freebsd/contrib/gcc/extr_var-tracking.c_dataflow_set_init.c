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
struct TYPE_3__ {scalar_t__ stack_adjust; int /*<<< orphan*/  vars; int /*<<< orphan*/  regs; } ;
typedef  TYPE_1__ dataflow_set ;

/* Variables and functions */
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_attrs_list_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  variable_htab_eq ; 
 int /*<<< orphan*/  variable_htab_free ; 
 int /*<<< orphan*/  variable_htab_hash ; 

__attribute__((used)) static void
dataflow_set_init (dataflow_set *set, int vars_size)
{
  init_attrs_list_set (set->regs);
  set->vars = htab_create (vars_size, variable_htab_hash, variable_htab_eq,
			   variable_htab_free);
  set->stack_adjust = 0;
}