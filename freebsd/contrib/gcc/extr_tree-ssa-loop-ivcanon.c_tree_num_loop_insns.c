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
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ estimate_num_insns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 

unsigned
tree_num_loop_insns (struct loop *loop)
{
  basic_block *body = get_loop_body (loop);
  block_stmt_iterator bsi;
  unsigned size = 1, i;

  for (i = 0; i < loop->num_nodes; i++)
    for (bsi = bsi_start (body[i]); !bsi_end_p (bsi); bsi_next (&bsi))
      size += estimate_num_insns (bsi_stmt (bsi));
  free (body);

  return size;
}