#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dtrace_hdl_t *
set_open_errno(dtrace_hdl_t *dtp, int *errp, int err)
{
	if (dtp != NULL)
		dtrace_close(dtp);
	if (errp != NULL)
		*errp = err;
	return (NULL);
}