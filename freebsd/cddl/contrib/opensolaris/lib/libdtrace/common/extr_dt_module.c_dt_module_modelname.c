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
struct TYPE_3__ {int /*<<< orphan*/ * dm_ops; } ;
typedef  TYPE_1__ dt_module_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_modops_64 ; 

const char *
dt_module_modelname(dt_module_t *dmp)
{
	if (dmp->dm_ops == &dt_modops_64)
		return ("64-bit");
	else
		return ("32-bit");
}