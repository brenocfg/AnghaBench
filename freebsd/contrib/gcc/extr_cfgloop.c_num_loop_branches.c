#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct loop {scalar_t__ latch; unsigned int num_nodes; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__** get_loop_body (struct loop const*) ; 

unsigned
num_loop_branches (const struct loop *loop)
{
  unsigned i, n;
  basic_block * body;

  gcc_assert (loop->latch != EXIT_BLOCK_PTR);

  body = get_loop_body (loop);
  n = 0;
  for (i = 0; i < loop->num_nodes; i++)
    if (EDGE_COUNT (body[i]->succs) >= 2)
      n++;
  free (body);

  return n;
}