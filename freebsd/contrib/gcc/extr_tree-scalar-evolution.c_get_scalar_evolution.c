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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  INTEGER_CST 130 
#define  REAL_CST 129 
#define  SSA_NAME 128 
 int TDF_DETAILS ; 
 int TDF_STATS ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_not_analyzed_yet ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/ * find_var_scev_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  nb_get_scev ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_scalar_evolution (tree scalar)
{
  tree res;
  
  if (dump_file)
    {
      if (dump_flags & TDF_DETAILS)
	{
	  fprintf (dump_file, "(get_scalar_evolution \n");
	  fprintf (dump_file, "  (scalar = ");
	  print_generic_expr (dump_file, scalar, 0);
	  fprintf (dump_file, ")\n");
	}
      if (dump_flags & TDF_STATS)
	nb_get_scev++;
    }
  
  switch (TREE_CODE (scalar))
    {
    case SSA_NAME:
      res = *find_var_scev_info (scalar);
      break;

    case REAL_CST:
    case INTEGER_CST:
      res = scalar;
      break;

    default:
      res = chrec_not_analyzed_yet;
      break;
    }
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (scalar_evolution = ");
      print_generic_expr (dump_file, res, 0);
      fprintf (dump_file, "))\n");
    }
  
  return res;
}