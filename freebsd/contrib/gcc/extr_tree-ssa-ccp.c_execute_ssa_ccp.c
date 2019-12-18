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
 int /*<<< orphan*/  ccp_finalize () ; 
 int /*<<< orphan*/  ccp_initialize () ; 
 int /*<<< orphan*/  ccp_visit_phi_node ; 
 int /*<<< orphan*/  ccp_visit_stmt ; 
 int do_store_ccp ; 
 int /*<<< orphan*/  ssa_propagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
execute_ssa_ccp (bool store_ccp)
{
  do_store_ccp = store_ccp;
  ccp_initialize ();
  ssa_propagate (ccp_visit_stmt, ccp_visit_phi_node);
  ccp_finalize ();
}