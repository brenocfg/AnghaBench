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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ALIGN_INDIRECT_REF ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ MISALIGNED_INDIRECT_REF ; 
 scalar_t__ RESULT_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_decl_name (int /*<<< orphan*/ *,scalar_t__) ; 

void
print_mem_expr (FILE *outfile, tree expr)
{
  if (TREE_CODE (expr) == COMPONENT_REF)
    {
      if (TREE_OPERAND (expr, 0))
	print_mem_expr (outfile, TREE_OPERAND (expr, 0));
      else
	fputs (" <variable>", outfile);
      fputc ('.', outfile);
      print_decl_name (outfile, TREE_OPERAND (expr, 1));
    }
  else if (TREE_CODE (expr) == INDIRECT_REF)
    {
      fputs (" (*", outfile);
      print_mem_expr (outfile, TREE_OPERAND (expr, 0));
      fputs (")", outfile);
    }
  else if (TREE_CODE (expr) == ALIGN_INDIRECT_REF)
    {
      fputs (" (A*", outfile);
      print_mem_expr (outfile, TREE_OPERAND (expr, 0));
      fputs (")", outfile);
    }
  else if (TREE_CODE (expr) == MISALIGNED_INDIRECT_REF)
    {
      fputs (" (M*", outfile);
      print_mem_expr (outfile, TREE_OPERAND (expr, 0));
      fputs (")", outfile);
    }
  else if (TREE_CODE (expr) == RESULT_DECL)
    fputs (" <result>", outfile);
  else
    {
      fputc (' ', outfile);
      print_decl_name (outfile, expr);
    }
}