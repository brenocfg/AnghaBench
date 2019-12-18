#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_optval_t ;
struct TYPE_6__ {int /*<<< orphan*/ * dt_sprintf_buf; int /*<<< orphan*/  dt_sprintf_buflen; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_printf_format (TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dtrace_getopt (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

int
dtrace_sprintf(dtrace_hdl_t *dtp, FILE *fp, void *fmtdata,
    const dtrace_recdesc_t *recp, uint_t nrecs, const void *buf, size_t len)
{
	dtrace_optval_t size;
	int rval;

	rval = dtrace_getopt(dtp, "strsize", &size);
	assert(rval == 0);
	assert(dtp->dt_sprintf_buflen == 0);

	if (dtp->dt_sprintf_buf != NULL)
		free(dtp->dt_sprintf_buf);

	if ((dtp->dt_sprintf_buf = malloc(size)) == NULL)
		return (dt_set_errno(dtp, EDT_NOMEM));

	bzero(dtp->dt_sprintf_buf, size);
	dtp->dt_sprintf_buflen = size;
	rval = dt_printf_format(dtp, fp, fmtdata, recp, nrecs, buf, len,
	    NULL, 0);
	dtp->dt_sprintf_buflen = 0;

	if (rval == -1)
		free(dtp->dt_sprintf_buf);

	return (rval);
}