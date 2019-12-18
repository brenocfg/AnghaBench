#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* di_dtor ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ dt_idops_t ;
struct TYPE_7__ {int /*<<< orphan*/ * di_data; void* di_iarg; TYPE_1__ const* di_ops; int /*<<< orphan*/  di_kind; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
dt_ident_morph(dt_ident_t *idp, ushort_t kind,
    const dt_idops_t *ops, void *iarg)
{
	idp->di_ops->di_dtor(idp);
	idp->di_kind = kind;
	idp->di_ops = ops;
	idp->di_iarg = iarg;
	idp->di_data = NULL;
}