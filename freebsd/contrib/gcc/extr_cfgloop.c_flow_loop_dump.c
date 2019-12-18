#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct loop {int num; int depth; int level; unsigned int num_nodes; TYPE_3__* outer; TYPE_2__* latch; TYPE_1__* header; } ;
typedef  TYPE_4__* basic_block ;
struct TYPE_10__ {int index; } ;
struct TYPE_9__ {int num; } ;
struct TYPE_8__ {int index; } ;
struct TYPE_7__ {int index; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_4__**) ; 
 TYPE_4__** get_loop_body (struct loop const*) ; 

void
flow_loop_dump (const struct loop *loop, FILE *file,
		void (*loop_dump_aux) (const struct loop *, FILE *, int),
		int verbose)
{
  basic_block *bbs;
  unsigned i;

  if (! loop || ! loop->header)
    return;

  fprintf (file, ";;\n;; Loop %d\n", loop->num);

  fprintf (file, ";;  header %d, latch %d\n",
	   loop->header->index, loop->latch->index);
  fprintf (file, ";;  depth %d, level %d, outer %ld\n",
	   loop->depth, loop->level,
	   (long) (loop->outer ? loop->outer->num : -1));

  fprintf (file, ";;  nodes:");
  bbs = get_loop_body (loop);
  for (i = 0; i < loop->num_nodes; i++)
    fprintf (file, " %d", bbs[i]->index);
  free (bbs);
  fprintf (file, "\n");

  if (loop_dump_aux)
    loop_dump_aux (loop, file, verbose);
}