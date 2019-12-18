#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF (scalar_t__,int) ; 
 TYPE_1__* PHI_ARG_EDGE (scalar_t__,int) ; 
 int PHI_NUM_ARGS (scalar_t__) ; 
 scalar_t__ flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
phi_loop_edge_uses_def (struct loop *loop, tree phi, tree def)
{
  int i;
  for (i = 0; i < PHI_NUM_ARGS (phi); i++)
    if (flow_bb_inside_loop_p (loop, PHI_ARG_EDGE (phi, i)->src))
      if (PHI_ARG_DEF (phi, i) == def)
	return true;
  return false;
}