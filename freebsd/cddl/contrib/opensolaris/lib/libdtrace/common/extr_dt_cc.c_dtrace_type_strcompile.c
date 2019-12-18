#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_typeinfo_t ;
struct TYPE_4__ {scalar_t__ dt_errno; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PROBESPEC_NONE ; 
 int /*<<< orphan*/  DT_CTX_DTYPE ; 
 int /*<<< orphan*/  dt_compile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int
dtrace_type_strcompile(dtrace_hdl_t *dtp, const char *s, dtrace_typeinfo_t *dtt)
{
	(void) dt_compile(dtp, DT_CTX_DTYPE,
	    DTRACE_PROBESPEC_NONE, dtt, 0, 0, NULL, NULL, s);
	return (dtp->dt_errno ? -1 : 0);
}