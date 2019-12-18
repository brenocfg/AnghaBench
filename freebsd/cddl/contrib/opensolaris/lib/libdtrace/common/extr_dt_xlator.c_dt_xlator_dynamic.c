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
struct TYPE_3__ {int /*<<< orphan*/ * dx_locals; } ;
typedef  TYPE_1__ dt_xlator_t ;

/* Variables and functions */

int
dt_xlator_dynamic(const dt_xlator_t *dxp)
{
	return (dxp->dx_locals == NULL);
}