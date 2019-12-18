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
struct loop {int /*<<< orphan*/  nb_iterations; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_type (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
set_nb_iterations_in_loop (struct loop *loop, 
			   tree res)
{
  tree type = chrec_type (res);

  res = chrec_fold_plus (type, res, build_int_cst (type, 1));

  /* FIXME HWI: However we want to store one iteration less than the
     count of the loop in order to be compatible with the other
     nb_iter computations in loop-iv.  This also allows the
     representation of nb_iters that are equal to MAX_INT.  */
  if (TREE_CODE (res) == INTEGER_CST
      && (TREE_INT_CST_LOW (res) == 0
	  || TREE_OVERFLOW (res)))
    res = chrec_dont_know;
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (set_nb_iterations_in_loop = ");
      print_generic_expr (dump_file, res, 0);
      fprintf (dump_file, "))\n");
    }
  
  loop->nb_iterations = res;
  return res;
}