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
struct TYPE_3__ {int dt_lazyload; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */

__attribute__((used)) static int
dt_opt_lazyload(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dtp->dt_lazyload = 1;

	return (0);
}