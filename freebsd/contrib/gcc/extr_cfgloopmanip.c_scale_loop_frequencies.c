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
struct loop {int /*<<< orphan*/  num_nodes; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  scale_bbs_frequencies_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
scale_loop_frequencies (struct loop *loop, int num, int den)
{
  basic_block *bbs;

  bbs = get_loop_body (loop);
  scale_bbs_frequencies_int (bbs, loop->num_nodes, num, den);
  free (bbs);
}