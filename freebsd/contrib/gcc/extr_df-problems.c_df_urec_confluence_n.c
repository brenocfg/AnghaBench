#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dataflow {int dummy; } ;
typedef  TYPE_3__* edge ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_9__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_8__ {int flags; TYPE_2__* src; TYPE_1__* dest; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EDGE_FAKE ; 
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* df_urec_get_bb_info (struct dataflow*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
df_urec_confluence_n (struct dataflow *dflow, edge e)
{
  bitmap op1 = df_urec_get_bb_info (dflow, e->dest->index)->in;
  bitmap op2 = df_urec_get_bb_info (dflow, e->src->index)->out;
 
  if (e->flags & EDGE_FAKE) 
    return;

  bitmap_ior_into (op1, op2);
}