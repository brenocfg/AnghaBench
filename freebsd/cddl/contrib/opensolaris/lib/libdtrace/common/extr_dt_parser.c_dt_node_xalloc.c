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
typedef  scalar_t__ uchar_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {int dn_line; int dn_reg; int /*<<< orphan*/  dn_u; int /*<<< orphan*/ * dn_link; int /*<<< orphan*/ * dn_list; int /*<<< orphan*/  dn_attr; scalar_t__ dn_op; scalar_t__ dn_flags; scalar_t__ dn_kind; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  _dtrace_defattr ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* dt_alloc (int /*<<< orphan*/ *,int) ; 

dt_node_t *
dt_node_xalloc(dtrace_hdl_t *dtp, int kind)
{
	dt_node_t *dnp = dt_alloc(dtp, sizeof (dt_node_t));

	if (dnp == NULL)
		return (NULL);

	dnp->dn_ctfp = NULL;
	dnp->dn_type = CTF_ERR;
	dnp->dn_kind = (uchar_t)kind;
	dnp->dn_flags = 0;
	dnp->dn_op = 0;
	dnp->dn_line = -1;
	dnp->dn_reg = -1;
	dnp->dn_attr = _dtrace_defattr;
	dnp->dn_list = NULL;
	dnp->dn_link = NULL;
	bzero(&dnp->dn_u, sizeof (dnp->dn_u));

	return (dnp);
}