#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* dtpda_edesc; } ;
typedef  TYPE_1__ dtrace_probedata_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_6__ {int dtepd_uarg; } ;
typedef  TYPE_2__ dtrace_eprobedesc_t ;

/* Variables and functions */
 int DTRACE_CONSUME_ERROR ; 
 int DTRACE_CONSUME_NEXT ; 
 int DTRACE_CONSUME_THIS ; 
#define  DT_ECB_ERROR 128 
 int dt_handle_err (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
dt_handle(dtrace_hdl_t *dtp, dtrace_probedata_t *data)
{
	dtrace_eprobedesc_t *epd = data->dtpda_edesc;
	int rval;

	switch (epd->dtepd_uarg) {
	case DT_ECB_ERROR:
		rval = dt_handle_err(dtp, data);
		break;

	default:
		return (DTRACE_CONSUME_THIS);
	}

	if (rval == 0)
		return (DTRACE_CONSUME_NEXT);

	return (DTRACE_CONSUME_ERROR);
}