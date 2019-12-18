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
struct ui_file {int dummy; } ;
struct expression {TYPE_1__* elts; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int dump_subexp_body (struct expression*,struct ui_file*,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int op_name (struct expression*,int /*<<< orphan*/ ) ; 

int
dump_subexp (struct expression *exp, struct ui_file *stream, int elt)
{
  static int indent = 0;
  int i;

  fprintf_filtered (stream, "\n");
  fprintf_filtered (stream, "\t%5d  ", elt);

  for (i = 1; i <= indent; i++)
    fprintf_filtered (stream, " ");
  indent += 2;

  fprintf_filtered (stream, "%-20s  ", op_name (exp, exp->elts[elt].opcode));

  elt = dump_subexp_body (exp, stream, elt);

  indent -= 2;

  return elt;
}