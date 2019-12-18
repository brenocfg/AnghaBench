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
 int /*<<< orphan*/ * bnx2fc_transport_template ; 
 int /*<<< orphan*/ * bnx2fc_vport_xport_template ; 
 int /*<<< orphan*/  fc_release_transport (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2fc_release_transport(void)
{
	fc_release_transport(bnx2fc_transport_template);
	fc_release_transport(bnx2fc_vport_xport_template);
	bnx2fc_transport_template = NULL;
	bnx2fc_vport_xport_template = NULL;
}