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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int dt_printf_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dtrace_fprintf(dtrace_hdl_t *dtp, FILE *fp, void *fmtdata,
    const dtrace_probedata_t *data, const dtrace_recdesc_t *recp,
    uint_t nrecs, const void *buf, size_t len)
{
	return (dt_printf_format(dtp, fp, fmtdata,
	    recp, nrecs, buf, len, NULL, 0));
}