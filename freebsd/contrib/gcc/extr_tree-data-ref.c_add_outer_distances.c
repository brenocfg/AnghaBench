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
typedef  int* lambda_vector ;

/* Variables and functions */
 int /*<<< orphan*/  DDR_NB_LOOPS (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  lambda_vector_copy (int*,int*,int /*<<< orphan*/ ) ; 
 int* lambda_vector_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_dist_v (struct data_dependence_relation*,int*) ; 

__attribute__((used)) static void
add_outer_distances (struct data_dependence_relation *ddr,
		     lambda_vector dist_v, int index)
{
  /* For each outer loop where init_v is not set, the accesses are
     in dependence of distance 1 in the loop.  */
  while (--index >= 0)
    {
      lambda_vector save_v = lambda_vector_new (DDR_NB_LOOPS (ddr));
      lambda_vector_copy (dist_v, save_v, DDR_NB_LOOPS (ddr));
      save_v[index] = 1;
      save_dist_v (ddr, save_v);
    }
}