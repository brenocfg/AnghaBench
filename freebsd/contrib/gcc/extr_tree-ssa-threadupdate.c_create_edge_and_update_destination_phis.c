#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct redirection_data {TYPE_1__* outgoing_edge; TYPE_4__* dup_block; } ;
typedef  TYPE_2__* edge ;
struct TYPE_8__ {int /*<<< orphan*/  count; } ;
struct TYPE_7__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  count; int /*<<< orphan*/  probability; } ;
struct TYPE_6__ {int dest_idx; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  PHI_ARG_DEF (scalar_t__,int) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  add_phi_arg (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* make_edge (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_edge_and_update_destination_phis (struct redirection_data *rd)
{
  edge e = make_edge (rd->dup_block, rd->outgoing_edge->dest, EDGE_FALLTHRU);
  tree phi;

  e->probability = REG_BR_PROB_BASE;
  e->count = rd->dup_block->count;

  /* If there are any PHI nodes at the destination of the outgoing edge
     from the duplicate block, then we will need to add a new argument
     to them.  The argument should have the same value as the argument
     associated with the outgoing edge stored in RD.  */
  for (phi = phi_nodes (e->dest); phi; phi = PHI_CHAIN (phi))
    {
      int indx = rd->outgoing_edge->dest_idx;
      add_phi_arg (phi, PHI_ARG_DEF (phi, indx), e);
    }
}