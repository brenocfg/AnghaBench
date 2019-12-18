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
struct loop {int num; } ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_SUPERLOOP_CHRECS ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  del_scev_info ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  eq_scev_info ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  hash_scev_info ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_parameters_1 (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
instantiate_parameters (struct loop *loop,
			tree chrec)
{
  tree res;
  htab_t cache = htab_create (10, hash_scev_info, eq_scev_info, del_scev_info);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "(instantiate_parameters \n");
      fprintf (dump_file, "  (loop_nb = %d)\n", loop->num);
      fprintf (dump_file, "  (chrec = ");
      print_generic_expr (dump_file, chrec, 0);
      fprintf (dump_file, ")\n");
    }
 
  res = instantiate_parameters_1 (loop, chrec, INSERT_SUPERLOOP_CHRECS, cache,
				  0);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (res = ");
      print_generic_expr (dump_file, res, 0);
      fprintf (dump_file, "))\n");
    }

  htab_delete (cache);
  
  return res;
}