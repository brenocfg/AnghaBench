#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* ddg_ptr ;
typedef  TYPE_2__* ddg_node_ptr ;
struct TYPE_6__ {scalar_t__ insn; } ;
struct TYPE_5__ {int num_nodes; TYPE_2__* nodes; } ;

/* Variables and functions */

ddg_node_ptr
get_node_of_insn (ddg_ptr g, rtx insn)
{
  int i;

  for (i = 0; i < g->num_nodes; i++)
    if (insn == g->nodes[i].insn)
      return &g->nodes[i];
  return NULL;
}