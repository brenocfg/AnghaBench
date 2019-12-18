#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* edge ;
typedef  int /*<<< orphan*/  bbro_basic_block_data ;
typedef  TYPE_4__* basic_block ;
struct TYPE_22__ {int start_of_trace; int in_trace; int end_of_trace; int /*<<< orphan*/ * node; int /*<<< orphan*/ * heap; } ;
struct TYPE_19__ {TYPE_1__* rtl; } ;
struct TYPE_21__ {int index; struct TYPE_21__* aux; TYPE_2__ il; } ;
struct TYPE_20__ {TYPE_4__* dest; } ;
struct TYPE_18__ {int visited; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_COPY_PARTITION (TYPE_4__*,TYPE_4__*) ; 
 int GET_ARRAY_SIZE (int) ; 
 int MAX (int,int) ; 
 int array_size ; 
 TYPE_5__* bbd ; 
 scalar_t__ dump_file ; 
 TYPE_4__* duplicate_block (TYPE_4__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int last_basic_block ; 
 TYPE_5__* xrealloc (TYPE_5__*,int) ; 

__attribute__((used)) static basic_block
copy_bb (basic_block old_bb, edge e, basic_block bb, int trace)
{
  basic_block new_bb;

  new_bb = duplicate_block (old_bb, e, bb);
  BB_COPY_PARTITION (new_bb, old_bb);

  gcc_assert (e->dest == new_bb);
  gcc_assert (!e->dest->il.rtl->visited);

  if (dump_file)
    fprintf (dump_file,
	     "Duplicated bb %d (created bb %d)\n",
	     old_bb->index, new_bb->index);
  new_bb->il.rtl->visited = trace;
  new_bb->aux = bb->aux;
  bb->aux = new_bb;

  if (new_bb->index >= array_size || last_basic_block > array_size)
    {
      int i;
      int new_size;

      new_size = MAX (last_basic_block, new_bb->index + 1);
      new_size = GET_ARRAY_SIZE (new_size);
      bbd = xrealloc (bbd, new_size * sizeof (bbro_basic_block_data));
      for (i = array_size; i < new_size; i++)
	{
	  bbd[i].start_of_trace = -1;
	  bbd[i].in_trace = -1;
	  bbd[i].end_of_trace = -1;
	  bbd[i].heap = NULL;
	  bbd[i].node = NULL;
	}
      array_size = new_size;

      if (dump_file)
	{
	  fprintf (dump_file,
		   "Growing the dynamic array to %d elements.\n",
		   array_size);
	}
    }

  bbd[new_bb->index].in_trace = trace;

  return new_bb;
}