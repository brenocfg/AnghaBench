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
struct TYPE_4__ {int /*<<< orphan*/ * dn_string; struct TYPE_4__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dt_decl_protoform(dt_node_t *fnp, dt_node_t *flist)
{
	dt_node_t *dnp;

	for (dnp = flist; dnp != fnp && dnp != NULL; dnp = dnp->dn_list) {
		if (dnp->dn_string != NULL &&
		    strcmp(dnp->dn_string, fnp->dn_string) == 0)
			return (B_TRUE);
	}

	return (B_FALSE);
}