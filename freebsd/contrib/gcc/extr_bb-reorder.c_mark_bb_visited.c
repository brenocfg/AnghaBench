#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* basic_block ;
struct TYPE_9__ {int /*<<< orphan*/ * node; int /*<<< orphan*/ * heap; } ;
struct TYPE_7__ {TYPE_1__* rtl; } ;
struct TYPE_8__ {size_t index; TYPE_2__ il; } ;
struct TYPE_6__ {int visited; } ;

/* Variables and functions */
 TYPE_5__* bbd ; 
 int /*<<< orphan*/  fibheap_delete_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mark_bb_visited (basic_block bb, int trace)
{
  bb->il.rtl->visited = trace;
  if (bbd[bb->index].heap)
    {
      fibheap_delete_node (bbd[bb->index].heap, bbd[bb->index].node);
      bbd[bb->index].heap = NULL;
      bbd[bb->index].node = NULL;
    }
}