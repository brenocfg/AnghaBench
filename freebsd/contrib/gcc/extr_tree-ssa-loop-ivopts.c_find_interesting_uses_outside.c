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
struct ivopts_data {int dummy; } ;
typedef  TYPE_1__* edge ;
struct TYPE_4__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,TYPE_1__*) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  find_interesting_uses_op (struct ivopts_data*,scalar_t__) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_interesting_uses_outside (struct ivopts_data *data, edge exit)
{
  tree phi, def;

  for (phi = phi_nodes (exit->dest); phi; phi = PHI_CHAIN (phi))
    {
      def = PHI_ARG_DEF_FROM_EDGE (phi, exit);
      find_interesting_uses_op (data, def);
    }
}