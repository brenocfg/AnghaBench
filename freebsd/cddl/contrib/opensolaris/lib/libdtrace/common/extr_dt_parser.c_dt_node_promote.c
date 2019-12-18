#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dn_attr; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  dt_attr_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_attr_assign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_type_promote (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
dt_node_promote(dt_node_t *lp, dt_node_t *rp, dt_node_t *dnp)
{
	dt_type_promote(lp, rp, &dnp->dn_ctfp, &dnp->dn_type);
	dt_node_type_assign(dnp, dnp->dn_ctfp, dnp->dn_type, B_FALSE);
	dt_node_attr_assign(dnp, dt_attr_min(lp->dn_attr, rp->dn_attr));
}