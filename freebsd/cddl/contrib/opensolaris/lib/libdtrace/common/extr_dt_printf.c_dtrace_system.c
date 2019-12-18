#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
struct TYPE_5__ {int /*<<< orphan*/  dt_sprintf_buf; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dtrace_sprintf (TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int system (int /*<<< orphan*/ ) ; 

int
dtrace_system(dtrace_hdl_t *dtp, FILE *fp, void *fmtdata,
    const dtrace_probedata_t *data, const dtrace_recdesc_t *recp,
    uint_t nrecs, const void *buf, size_t len)
{
	int rval = dtrace_sprintf(dtp, fp, fmtdata, recp, nrecs, buf, len);

	if (rval == -1)
		return (rval);

	/*
	 * Before we execute the specified command, flush fp to assure that
	 * any prior dt_printf()'s appear before the output of the command
	 * not after it.
	 */
	(void) fflush(fp);

	if (system(dtp->dt_sprintf_buf) == -1)
		return (dt_set_errno(dtp, errno));

	return (rval);
}