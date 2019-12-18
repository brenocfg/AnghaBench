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
struct loops {unsigned int num; struct loop** parray; } ;
struct loop {int /*<<< orphan*/ * aux; } ;
typedef  int /*<<< orphan*/ * loop_vec_info ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOP_VINFO_VECTORIZABLE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REPORT_VECTORIZED_LOOPS ; 
 int /*<<< orphan*/  UNKNOWN_LOC ; 
 int /*<<< orphan*/  destroy_loop_vec_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_loop_location (struct loop*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/ * vect_analyze_loop (struct loop*) ; 
 int /*<<< orphan*/  vect_dump ; 
 int /*<<< orphan*/  vect_loop_location ; 
 unsigned int vect_loops_num ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_set_dump_settings () ; 
 int /*<<< orphan*/  vect_transform_loop (int /*<<< orphan*/ *,struct loops*) ; 
 int /*<<< orphan*/  vect_vnames_to_rename ; 

void
vectorize_loops (struct loops *loops)
{
  unsigned int i;
  unsigned int num_vectorized_loops = 0;

  /* Fix the verbosity level if not defined explicitly by the user.  */
  vect_set_dump_settings ();

  /* Allocate the bitmap that records which virtual variables that 
     need to be renamed.  */
  vect_vnames_to_rename = BITMAP_ALLOC (NULL);

  /*  ----------- Analyze loops. -----------  */

  /* If some loop was duplicated, it gets bigger number 
     than all previously defined loops. This fact allows us to run 
     only over initial loops skipping newly generated ones.  */
  vect_loops_num = loops->num;
  for (i = 1; i < vect_loops_num; i++)
    {
      loop_vec_info loop_vinfo;
      struct loop *loop = loops->parray[i];

      if (!loop)
        continue;

      vect_loop_location = find_loop_location (loop);
      loop_vinfo = vect_analyze_loop (loop);
      loop->aux = loop_vinfo;

      if (!loop_vinfo || !LOOP_VINFO_VECTORIZABLE_P (loop_vinfo))
	continue;

      vect_transform_loop (loop_vinfo, loops);
      num_vectorized_loops++;
    }
  vect_loop_location = UNKNOWN_LOC;

  if (vect_print_dump_info (REPORT_VECTORIZED_LOOPS))
    fprintf (vect_dump, "vectorized %u loops in function.\n",
	     num_vectorized_loops);

  /*  ----------- Finalize. -----------  */

  BITMAP_FREE (vect_vnames_to_rename);

  for (i = 1; i < vect_loops_num; i++)
    {
      struct loop *loop = loops->parray[i];
      loop_vec_info loop_vinfo;

      if (!loop)
	continue;
      loop_vinfo = loop->aux;
      destroy_loop_vec_info (loop_vinfo);
      loop->aux = NULL;
    }
}