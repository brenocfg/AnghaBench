#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 TYPE_1__* find_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* unchecked_make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

edge
make_edge (basic_block src, basic_block dest, int flags)
{
  edge e = find_edge (src, dest);

  /* Make sure we don't add duplicate edges.  */
  if (e)
    {
      e->flags |= flags;
      return NULL;
    }

  return unchecked_make_edge (src, dest, flags);
}