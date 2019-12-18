#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* constraint_t ;
typedef  int /*<<< orphan*/  constraint_graph_t ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_12__ {int /*<<< orphan*/  solution; int /*<<< orphan*/  is_special_var; } ;
struct TYPE_10__ {scalar_t__ type; unsigned int var; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {scalar_t__ type; unsigned int var; } ;
struct TYPE_11__ {TYPE_2__ rhs; TYPE_1__ lhs; } ;

/* Variables and functions */
 scalar_t__ ADDRESSOF ; 
 scalar_t__ DEREF ; 
 scalar_t__ SCALAR ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TEST_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  changed ; 
 int /*<<< orphan*/  changed_count ; 
 int /*<<< orphan*/  do_da_constraint (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_ds_constraint (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_sd_constraint (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 unsigned int find (unsigned int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_4__* get_varinfo (unsigned int) ; 
 int set_union_with_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_complex_constraint (constraint_graph_t graph, constraint_t c, bitmap delta)
{
  if (c->lhs.type == DEREF)
    {
      if (c->rhs.type == ADDRESSOF)
	{
	  /* *x = &y */
	  do_da_constraint (graph, c, delta);
	}
      else
	{
	  /* *x = y */
	  do_ds_constraint (c, delta);
	}
    }
  else if (c->rhs.type == DEREF)
    {
      /* x = *y */
      if (!(get_varinfo (c->lhs.var)->is_special_var))
	do_sd_constraint (graph, c, delta);
    }
  else
    {
      bitmap tmp;
      bitmap solution;
      bool flag = false;
      unsigned int t;

      gcc_assert (c->rhs.type == SCALAR && c->lhs.type == SCALAR);
      t = find (c->rhs.var);
      solution = get_varinfo (t)->solution;
      t = find (c->lhs.var);
      tmp = get_varinfo (t)->solution;

      flag = set_union_with_increment (tmp, solution, c->rhs.offset);

      if (flag)
	{
	  get_varinfo (t)->solution = tmp;
	  if (!TEST_BIT (changed, t))
	    {
	      SET_BIT (changed, t);
	      changed_count++;
	    }
	}
    }
}