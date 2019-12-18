#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dis_args; } ;
typedef  TYPE_1__ dt_idsig_t ;
struct TYPE_5__ {int /*<<< orphan*/ * di_data; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dt_iddtor_sign(dt_ident_t *idp)
{
	if (idp->di_data != NULL)
		free(((dt_idsig_t *)idp->di_data)->dis_args);
	free(idp->di_data);
}