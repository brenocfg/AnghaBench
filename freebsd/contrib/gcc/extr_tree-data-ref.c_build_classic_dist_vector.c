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
struct data_dependence_relation {int dummy; } ;
typedef  int /*<<< orphan*/  lambda_vector ;

/* Variables and functions */
 int /*<<< orphan*/  DDR_A (struct data_dependence_relation*) ; 
 scalar_t__ DDR_ARE_DEPENDENT (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_B (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_DIST_VECT (struct data_dependence_relation*,unsigned int) ; 
 int DDR_NB_LOOPS (struct data_dependence_relation*) ; 
 unsigned int DDR_NUM_DIST_VECTS (struct data_dependence_relation*) ; 
 scalar_t__ NULL_TREE ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  add_other_self_distances (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  add_outer_distances (struct data_dependence_relation*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_classic_dist_vector_1 (struct data_dependence_relation*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  compute_subscript_distance (struct data_dependence_relation*) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  lambda_vector_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lambda_vector_first_nz (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lambda_vector_lexico_pos (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lambda_vector_new (int) ; 
 int /*<<< orphan*/  print_lambda_vector (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ same_access_functions (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  save_dist_v (struct data_dependence_relation*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscript_dependence_tester_1 (struct data_dependence_relation*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
build_classic_dist_vector (struct data_dependence_relation *ddr)
{
  bool init_b = false;
  int index_carry = DDR_NB_LOOPS (ddr);
  lambda_vector dist_v;

  if (DDR_ARE_DEPENDENT (ddr) != NULL_TREE)
    return true;

  if (same_access_functions (ddr))
    {
      /* Save the 0 vector.  */
      dist_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
      save_dist_v (ddr, dist_v);

      if (DDR_NB_LOOPS (ddr) > 1)
	add_other_self_distances (ddr);

      return true;
    }

  dist_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
  if (!build_classic_dist_vector_1 (ddr, DDR_A (ddr), DDR_B (ddr),
				    dist_v, &init_b, &index_carry))
    return false;

  /* Save the distance vector if we initialized one.  */
  if (init_b)
    {
      /* Verify a basic constraint: classic distance vectors should
	 always be lexicographically positive.

	 Data references are collected in the order of execution of
	 the program, thus for the following loop

	 | for (i = 1; i < 100; i++)
	 |   for (j = 1; j < 100; j++)
	 |     {
	 |       t = T[j+1][i-1];  // A
	 |       T[j][i] = t + 2;  // B
	 |     }

	 references are collected following the direction of the wind:
	 A then B.  The data dependence tests are performed also
	 following this order, such that we're looking at the distance
	 separating the elements accessed by A from the elements later
	 accessed by B.  But in this example, the distance returned by
	 test_dep (A, B) is lexicographically negative (-1, 1), that
	 means that the access A occurs later than B with respect to
	 the outer loop, ie. we're actually looking upwind.  In this
	 case we solve test_dep (B, A) looking downwind to the
	 lexicographically positive solution, that returns the
	 distance vector (1, -1).  */
      if (!lambda_vector_lexico_pos (dist_v, DDR_NB_LOOPS (ddr)))
	{
	  lambda_vector save_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
	  subscript_dependence_tester_1 (ddr, DDR_B (ddr), DDR_A (ddr));
	  compute_subscript_distance (ddr);
	  build_classic_dist_vector_1 (ddr, DDR_B (ddr), DDR_A (ddr),
				       save_v, &init_b, &index_carry);
	  save_dist_v (ddr, save_v);

	  /* In this case there is a dependence forward for all the
	     outer loops:

	     | for (k = 1; k < 100; k++)
	     |  for (i = 1; i < 100; i++)
	     |   for (j = 1; j < 100; j++)
	     |     {
	     |       t = T[j+1][i-1];  // A
	     |       T[j][i] = t + 2;  // B
	     |     }

	     the vectors are: 
	     (0,  1, -1)
	     (1,  1, -1)
	     (1, -1,  1)
	  */
	  if (DDR_NB_LOOPS (ddr) > 1)
	    {
 	      add_outer_distances (ddr, save_v, index_carry);
	      add_outer_distances (ddr, dist_v, index_carry);
	    }
	}
      else
	{
	  lambda_vector save_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
	  lambda_vector_copy (dist_v, save_v, DDR_NB_LOOPS (ddr));
	  save_dist_v (ddr, save_v);

	  if (DDR_NB_LOOPS (ddr) > 1)
	    {
	      lambda_vector opposite_v = lambda_vector_new (DDR_NB_LOOPS (ddr));

	      subscript_dependence_tester_1 (ddr, DDR_B (ddr), DDR_A (ddr));
	      compute_subscript_distance (ddr);
	      build_classic_dist_vector_1 (ddr, DDR_B (ddr), DDR_A (ddr),
					   opposite_v, &init_b, &index_carry);

	      add_outer_distances (ddr, dist_v, index_carry);
	      add_outer_distances (ddr, opposite_v, index_carry);
	    }
	}
    }
  else
    {
      /* There is a distance of 1 on all the outer loops: Example:
	 there is a dependence of distance 1 on loop_1 for the array A.

	 | loop_1
	 |   A[5] = ...
	 | endloop
      */
      add_outer_distances (ddr, dist_v,
			   lambda_vector_first_nz (dist_v,
						   DDR_NB_LOOPS (ddr), 0));
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      unsigned i;

      fprintf (dump_file, "(build_classic_dist_vector\n");
      for (i = 0; i < DDR_NUM_DIST_VECTS (ddr); i++)
	{
	  fprintf (dump_file, "  dist_vector = (");
	  print_lambda_vector (dump_file, DDR_DIST_VECT (ddr, i),
			       DDR_NB_LOOPS (ddr));
	  fprintf (dump_file, "  )\n");
	}
      fprintf (dump_file, ")\n");
    }

  return true;
}