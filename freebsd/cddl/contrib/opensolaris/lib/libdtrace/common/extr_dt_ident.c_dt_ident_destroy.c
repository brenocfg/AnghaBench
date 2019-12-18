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
struct TYPE_7__ {struct TYPE_7__* di_name; TYPE_1__* di_ops; } ;
typedef  TYPE_2__ dt_ident_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* di_dtor ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
dt_ident_destroy(dt_ident_t *idp)
{
	idp->di_ops->di_dtor(idp);
	free(idp->di_name);
	free(idp);
}