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
struct bfa_vport_attr_s {int /*<<< orphan*/  vport_state; int /*<<< orphan*/  port_attr; } ;
struct bfa_fcs_vport_s {int /*<<< orphan*/  sm; int /*<<< orphan*/  lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcs_lport_get_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_to_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bfa_vport_attr_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vport_sm_table ; 

void
bfa_fcs_vport_get_attr(struct bfa_fcs_vport_s *vport,
			struct bfa_vport_attr_s *attr)
{
	if (vport == NULL || attr == NULL)
		return;

	memset(attr, 0, sizeof(struct bfa_vport_attr_s));

	bfa_fcs_lport_get_attr(&vport->lport, &attr->port_attr);
	attr->vport_state = bfa_sm_to_state(vport_sm_table, vport->sm);
}