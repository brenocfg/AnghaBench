#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dtrace_recdesc_t ;
typedef  int /*<<< orphan*/  dtrace_probedata_t ;
struct TYPE_6__ {scalar_t__ dt_buffered_offs; char* dt_buffered_buf; scalar_t__ (* dt_bufhdlr ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dt_bufarg; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_7__ {char* dtbda_buffered; int /*<<< orphan*/  dtbda_flags; int /*<<< orphan*/  const* dtbda_aggdata; int /*<<< orphan*/  const* dtbda_recdesc; int /*<<< orphan*/ * dtbda_probe; TYPE_1__* dtbda_handle; } ;
typedef  TYPE_2__ dtrace_bufdata_t ;
typedef  int /*<<< orphan*/  dtrace_aggdata_t ;

/* Variables and functions */
 scalar_t__ DTRACE_HANDLE_ABORT ; 
 int /*<<< orphan*/  EDT_DIRABORT ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
dt_buffered_flush(dtrace_hdl_t *dtp, dtrace_probedata_t *pdata,
    const dtrace_recdesc_t *rec, const dtrace_aggdata_t *agg, uint32_t flags)
{
	dtrace_bufdata_t data;

	if (dtp->dt_buffered_offs == 0)
		return (0);

	data.dtbda_handle = dtp;
	data.dtbda_buffered = dtp->dt_buffered_buf;
	data.dtbda_probe = pdata;
	data.dtbda_recdesc = rec;
	data.dtbda_aggdata = agg;
	data.dtbda_flags = flags;

	if ((*dtp->dt_bufhdlr)(&data, dtp->dt_bufarg) == DTRACE_HANDLE_ABORT)
		return (dt_set_errno(dtp, EDT_DIRABORT));

	dtp->dt_buffered_offs = 0;
	dtp->dt_buffered_buf[0] = '\0';

	return (0);
}