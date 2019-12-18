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
typedef  int /*<<< orphan*/  dt_node_t ;
struct TYPE_3__ {scalar_t__ di_type; int /*<<< orphan*/ * di_ctfp; } ;
typedef  TYPE_1__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ CTF_ERR ; 
 int /*<<< orphan*/  dt_node_type_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_idcook_thaw(dt_node_t *dnp, dt_ident_t *idp, int argc, dt_node_t *args)
{
	if (idp->di_ctfp != NULL && idp->di_type != CTF_ERR)
		dt_node_type_assign(dnp, idp->di_ctfp, idp->di_type, B_FALSE);
}