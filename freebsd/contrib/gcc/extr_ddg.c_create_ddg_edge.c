#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ddg_edge {int dummy; } ;
typedef  int /*<<< orphan*/  dep_type ;
typedef  int /*<<< orphan*/  dep_data_type ;
typedef  void* ddg_node_ptr ;
typedef  TYPE_2__* ddg_edge_ptr ;
struct TYPE_4__ {scalar_t__ info; } ;
struct TYPE_5__ {int latency; int distance; TYPE_1__ aux; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  next_in; int /*<<< orphan*/  data_type; int /*<<< orphan*/  type; void* dest; void* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmalloc (int) ; 

__attribute__((used)) static ddg_edge_ptr
create_ddg_edge (ddg_node_ptr src, ddg_node_ptr dest,
		 dep_type t, dep_data_type dt, int l, int d)
{
  ddg_edge_ptr e = (ddg_edge_ptr) xmalloc (sizeof (struct ddg_edge));

  e->src = src;
  e->dest = dest;
  e->type = t;
  e->data_type = dt;
  e->latency = l;
  e->distance = d;
  e->next_in = e->next_out = NULL;
  e->aux.info = 0;
  return e;
}