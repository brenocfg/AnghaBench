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
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {scalar_t__ phi_nodes; } ;

/* Variables and functions */
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  set_bb_for_stmt (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static inline void
set_phi_nodes (basic_block bb, tree l)
{
  tree phi;

  bb->phi_nodes = l;
  for (phi = l; phi; phi = PHI_CHAIN (phi))
    set_bb_for_stmt (phi, bb);
}