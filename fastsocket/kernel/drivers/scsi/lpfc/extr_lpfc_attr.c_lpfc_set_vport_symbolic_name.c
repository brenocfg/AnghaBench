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
struct lpfc_vport {scalar_t__ port_state; } ;
struct fc_vport {scalar_t__ dd_data; } ;

/* Variables and functions */
 scalar_t__ LPFC_VPORT_READY ; 
 int /*<<< orphan*/  SLI_CTNS_RSPN_ID ; 
 int /*<<< orphan*/  lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_set_vport_symbolic_name(struct fc_vport *fc_vport)
{
	struct lpfc_vport *vport = *(struct lpfc_vport **)fc_vport->dd_data;

	if (vport->port_state == LPFC_VPORT_READY)
		lpfc_ns_cmd(vport, SLI_CTNS_RSPN_ID, 0, 0);
}