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
typedef  int /*<<< orphan*/  tree ;
struct loop {TYPE_1__* single_exit; } ;
typedef  TYPE_1__* edge ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int TDF_DETAILS ; 
 scalar_t__ analyzable_condition (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree 
get_loop_exit_condition (struct loop *loop)
{
  tree res = NULL_TREE;
  edge exit_edge = loop->single_exit;

  
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(get_loop_exit_condition \n  ");
  
  if (exit_edge)
    {
      tree expr;
      
      expr = last_stmt (exit_edge->src);
      if (analyzable_condition (expr))
	res = expr;
    }
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      print_generic_expr (dump_file, res, 0);
      fprintf (dump_file, ")\n");
    }
  
  return res;
}