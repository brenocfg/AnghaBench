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
struct data_reference {int dummy; } ;
struct data_dependence_relation {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_dependence_undetermined; int /*<<< orphan*/  num_dependence_tests; } ;

/* Variables and functions */
 struct data_reference* DDR_A (struct data_dependence_relation*) ; 
 scalar_t__ DDR_ARE_DEPENDENT (struct data_dependence_relation*) ; 
 struct data_reference* DDR_B (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DR_STMT (struct data_reference*) ; 
 scalar_t__ NULL_TREE ; 
 int TDF_DETAILS ; 
 scalar_t__ access_functions_are_affine_or_constant_p (struct data_reference*) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 TYPE_1__ dependence_stats ; 
 int /*<<< orphan*/  dump_data_reference (scalar_t__,struct data_reference*) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  finalize_ddr_dependent (struct data_dependence_relation*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscript_dependence_tester (struct data_dependence_relation*) ; 

__attribute__((used)) static void
compute_affine_dependence (struct data_dependence_relation *ddr)
{
  struct data_reference *dra = DDR_A (ddr);
  struct data_reference *drb = DDR_B (ddr);
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "(compute_affine_dependence\n");
      fprintf (dump_file, "  (stmt_a = \n");
      print_generic_expr (dump_file, DR_STMT (dra), 0);
      fprintf (dump_file, ")\n  (stmt_b = \n");
      print_generic_expr (dump_file, DR_STMT (drb), 0);
      fprintf (dump_file, ")\n");
    }

  /* Analyze only when the dependence relation is not yet known.  */
  if (DDR_ARE_DEPENDENT (ddr) == NULL_TREE)
    {
      dependence_stats.num_dependence_tests++;

      if (access_functions_are_affine_or_constant_p (dra)
	  && access_functions_are_affine_or_constant_p (drb))
	subscript_dependence_tester (ddr);
      
      /* As a last case, if the dependence cannot be determined, or if
	 the dependence is considered too difficult to determine, answer
	 "don't know".  */
      else
	{
	  dependence_stats.num_dependence_undetermined++;

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "Data ref a:\n");
	      dump_data_reference (dump_file, dra);
	      fprintf (dump_file, "Data ref b:\n");
	      dump_data_reference (dump_file, drb);
	      fprintf (dump_file, "affine dependence test not usable: access function not affine or constant.\n");
	    }
	  finalize_ddr_dependent (ddr, chrec_dont_know);
	}
    }
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ")\n");
}