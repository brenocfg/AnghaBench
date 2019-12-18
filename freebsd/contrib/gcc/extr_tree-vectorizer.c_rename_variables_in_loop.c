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
struct loop {unsigned int num_nodes; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  rename_variables_in_bb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rename_variables_in_loop (struct loop *loop)
{
  unsigned i;
  basic_block *bbs;

  bbs = get_loop_body (loop);

  for (i = 0; i < loop->num_nodes; i++)
    rename_variables_in_bb (bbs[i]);

  free (bbs);
}