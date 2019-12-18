#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ refcount; scalar_t__ fix_size; int /*<<< orphan*/  offset; struct TYPE_3__* next; } ;
typedef  TYPE_1__ Mnode ;
typedef  int /*<<< orphan*/  Mfix ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/ * minipool_barrier ; 
 TYPE_1__* minipool_vector_head ; 

__attribute__((used)) static void
assign_minipool_offsets (Mfix *barrier)
{
  HOST_WIDE_INT offset = 0;
  Mnode *mp;

  minipool_barrier = barrier;

  for (mp = minipool_vector_head; mp != NULL; mp = mp->next)
    {
      mp->offset = offset;

      if (mp->refcount > 0)
	offset += mp->fix_size;
    }
}