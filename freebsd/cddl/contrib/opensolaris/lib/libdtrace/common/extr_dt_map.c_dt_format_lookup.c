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
struct TYPE_3__ {int dt_maxformat; void** dt_formats; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */

void *
dt_format_lookup(dtrace_hdl_t *dtp, int format)
{
	if (format == 0 || format > dtp->dt_maxformat)
		return (NULL);

	if (dtp->dt_formats == NULL)
		return (NULL);

	return (dtp->dt_formats[format - 1]);
}