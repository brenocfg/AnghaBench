#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,TYPE_1__*) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
propagate_through_phis (tree var, edge e)
{
  basic_block dest = e->dest;
  tree phi;

  for (phi = phi_nodes (dest); phi; phi = PHI_CHAIN (phi))
    if (PHI_ARG_DEF_FROM_EDGE (phi, e) == var)
      return PHI_RESULT (phi);

  return var;
}