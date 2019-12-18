#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  void* basic_block ;
struct TYPE_7__ {int flags; void* dest; void* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_dest (TYPE_1__*) ; 
 int /*<<< orphan*/  connect_src (TYPE_1__*) ; 
 int /*<<< orphan*/  execute_on_growing_pred (TYPE_1__*) ; 
 TYPE_1__* ggc_alloc_cleared (int) ; 
 int /*<<< orphan*/  n_edges ; 

edge
unchecked_make_edge (basic_block src, basic_block dst, int flags)
{
  edge e;
  e = ggc_alloc_cleared (sizeof (*e));
  n_edges++;

  e->src = src;
  e->dest = dst;
  e->flags = flags;

  connect_src (e);
  connect_dest (e);

  execute_on_growing_pred (e);

  return e;
}