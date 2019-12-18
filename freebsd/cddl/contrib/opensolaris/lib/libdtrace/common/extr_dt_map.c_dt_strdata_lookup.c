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
struct TYPE_3__ {int dt_maxstrdata; char const** dt_strdata; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */

const char *
dt_strdata_lookup(dtrace_hdl_t *dtp, int idx)
{
	if (idx == 0 || idx > dtp->dt_maxstrdata)
		return (NULL);

	if (dtp->dt_strdata == NULL)
		return (NULL);

	return (dtp->dt_strdata[idx - 1]);
}