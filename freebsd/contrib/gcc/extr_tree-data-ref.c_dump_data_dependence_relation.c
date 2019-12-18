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
struct loop {int num; } ;
struct data_reference {int dummy; } ;
struct data_dependence_relation {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct data_reference* DDR_A (struct data_dependence_relation*) ; 
 scalar_t__ DDR_ARE_DEPENDENT (struct data_dependence_relation*) ; 
 struct data_reference* DDR_B (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_DIR_VECT (struct data_dependence_relation*,unsigned int) ; 
 int /*<<< orphan*/  DDR_DIST_VECT (struct data_dependence_relation*,unsigned int) ; 
 int /*<<< orphan*/  DDR_LOOP_NEST (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_NB_LOOPS (struct data_dependence_relation*) ; 
 unsigned int DDR_NUM_DIR_VECTS (struct data_dependence_relation*) ; 
 unsigned int DDR_NUM_DIST_VECTS (struct data_dependence_relation*) ; 
 unsigned int DDR_NUM_SUBSCRIPTS (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_SUBSCRIPT (struct data_dependence_relation*,unsigned int) ; 
 int /*<<< orphan*/  DR_ACCESS_FN (struct data_reference*,unsigned int) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ VEC_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct loop*) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ chrec_known ; 
 int /*<<< orphan*/  dump_subscript (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  loop_p ; 
 int /*<<< orphan*/  print_direction_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_stmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lambda_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
dump_data_dependence_relation (FILE *outf, 
			       struct data_dependence_relation *ddr)
{
  struct data_reference *dra, *drb;

  dra = DDR_A (ddr);
  drb = DDR_B (ddr);
  fprintf (outf, "(Data Dep: \n");
  if (DDR_ARE_DEPENDENT (ddr) == chrec_dont_know)
    fprintf (outf, "    (don't know)\n");
  
  else if (DDR_ARE_DEPENDENT (ddr) == chrec_known)
    fprintf (outf, "    (no dependence)\n");
  
  else if (DDR_ARE_DEPENDENT (ddr) == NULL_TREE)
    {
      unsigned int i;
      struct loop *loopi;

      for (i = 0; i < DDR_NUM_SUBSCRIPTS (ddr); i++)
	{
	  fprintf (outf, "  access_fn_A: ");
	  print_generic_stmt (outf, DR_ACCESS_FN (dra, i), 0);
	  fprintf (outf, "  access_fn_B: ");
	  print_generic_stmt (outf, DR_ACCESS_FN (drb, i), 0);
	  dump_subscript (outf, DDR_SUBSCRIPT (ddr, i));
	}

      fprintf (outf, "  loop nest: (");
      for (i = 0; VEC_iterate (loop_p, DDR_LOOP_NEST (ddr), i, loopi); i++)
	fprintf (outf, "%d ", loopi->num);
      fprintf (outf, ")\n");

      for (i = 0; i < DDR_NUM_DIST_VECTS (ddr); i++)
	{
	  fprintf (outf, "  distance_vector: ");
	  print_lambda_vector (outf, DDR_DIST_VECT (ddr, i),
			       DDR_NB_LOOPS (ddr));
	}

      for (i = 0; i < DDR_NUM_DIR_VECTS (ddr); i++)
	{
	  fprintf (outf, "  direction_vector: ");
	  print_direction_vector (outf, DDR_DIR_VECT (ddr, i),
				  DDR_NB_LOOPS (ddr));
	}
    }

  fprintf (outf, ")\n");
}