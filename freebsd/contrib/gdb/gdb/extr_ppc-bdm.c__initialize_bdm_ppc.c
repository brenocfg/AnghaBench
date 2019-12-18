#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdm_ppc_ops ; 
 int /*<<< orphan*/  init_bdm_ppc_ops () ; 

void
_initialize_bdm_ppc (void)
{
  init_bdm_ppc_ops ();
  add_target (&bdm_ppc_ops);
}