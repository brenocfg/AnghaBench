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
typedef  scalar_t__ tree ;
typedef  TYPE_1__* edge ;
struct TYPE_3__ {int /*<<< orphan*/  dest_idx; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_phi_arg_num (scalar_t__,int /*<<< orphan*/ ) ; 

void
remove_phi_args (edge e)
{
  tree phi;

  for (phi = phi_nodes (e->dest); phi; phi = PHI_CHAIN (phi))
    remove_phi_arg_num (phi, e->dest_idx);
}