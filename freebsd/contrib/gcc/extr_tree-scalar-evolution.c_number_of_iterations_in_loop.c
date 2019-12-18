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
struct tree_niter_desc {scalar_t__ niter; int /*<<< orphan*/  may_be_zero; } ;
struct loop {int /*<<< orphan*/  single_exit; scalar_t__ nb_iterations; } ;
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int TDF_DETAILS ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ integer_nonzerop (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_iterations_exit (struct loop*,int /*<<< orphan*/ ,struct tree_niter_desc*,int) ; 
 scalar_t__ set_nb_iterations_in_loop (struct loop*,scalar_t__) ; 

tree 
number_of_iterations_in_loop (struct loop *loop)
{
  tree res, type;
  edge exit;
  struct tree_niter_desc niter_desc;

  /* Determine whether the number_of_iterations_in_loop has already
     been computed.  */
  res = loop->nb_iterations;
  if (res)
    return res;
  res = chrec_dont_know;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(number_of_iterations_in_loop\n");
  
  exit = loop->single_exit;
  if (!exit)
    goto end;

  if (!number_of_iterations_exit (loop, exit, &niter_desc, false))
    goto end;

  type = TREE_TYPE (niter_desc.niter);
  if (integer_nonzerop (niter_desc.may_be_zero))
    res = build_int_cst (type, 0);
  else if (integer_zerop (niter_desc.may_be_zero))
    res = niter_desc.niter;
  else
    res = chrec_dont_know;

end:
  return set_nb_iterations_in_loop (loop, res);
}