#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* lines; TYPE_3__* name; struct TYPE_10__* next; } ;
typedef  TYPE_1__ source_t ;
struct TYPE_11__ {unsigned int num_blocks; TYPE_3__* counts; TYPE_3__* blocks; struct TYPE_11__* next; } ;
typedef  TYPE_2__ function_t ;
struct TYPE_12__ {struct TYPE_12__* succ_next; struct TYPE_12__* succ; } ;
typedef  TYPE_3__ block_t ;
typedef  TYPE_3__ arc_t ;

/* Variables and functions */
 TYPE_3__* bbg_file_name ; 
 scalar_t__ bbg_file_time ; 
 scalar_t__ bbg_stamp ; 
 TYPE_3__* da_file_name ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_2__* functions ; 
 TYPE_1__* sources ; 

__attribute__((used)) static void
release_structures (void)
{
  function_t *fn;
  source_t *src;

  free (bbg_file_name);
  free (da_file_name);
  da_file_name = bbg_file_name = NULL;
  bbg_file_time = 0;
  bbg_stamp = 0;

  while ((src = sources))
    {
      sources = src->next;

      free (src->name);
      free (src->lines);
    }

  while ((fn = functions))
    {
      unsigned ix;
      block_t *block;

      functions = fn->next;
      for (ix = fn->num_blocks, block = fn->blocks; ix--; block++)
	{
	  arc_t *arc, *arc_n;

	  for (arc = block->succ; arc; arc = arc_n)
	    {
	      arc_n = arc->succ_next;
	      free (arc);
	    }
	}
      free (fn->blocks);
      free (fn->counts);
    }
}