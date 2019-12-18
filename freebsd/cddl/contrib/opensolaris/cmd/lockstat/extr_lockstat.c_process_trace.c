#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsrec_t ;
struct TYPE_5__ {scalar_t__ lsd_count; int /*<<< orphan*/ * lsd_next; } ;
typedef  TYPE_1__ lsdata_t ;
struct TYPE_6__ {int /*<<< orphan*/  dtpda_data; TYPE_3__* dtpda_edesc; } ;
typedef  TYPE_2__ dtrace_probedata_t ;
struct TYPE_7__ {int /*<<< orphan*/  dtepd_nrecs; int /*<<< orphan*/  dtepd_rec; } ;
typedef  TYPE_3__ dtrace_eprobedesc_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int DTRACE_CONSUME_NEXT ; 
 scalar_t__ g_nrecs ; 
 scalar_t__ g_recsize ; 
 int /*<<< orphan*/  lsrec_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
process_trace(const dtrace_probedata_t *pdata, void *arg)
{
	lsdata_t *lsdata = arg;
	lsrec_t *lsrec = lsdata->lsd_next;
	dtrace_eprobedesc_t *edesc = pdata->dtpda_edesc;
	caddr_t data = pdata->dtpda_data;

	if (lsdata->lsd_count >= g_nrecs)
		return (DTRACE_CONSUME_NEXT);

	lsrec_fill(lsrec, edesc->dtepd_rec, edesc->dtepd_nrecs, data);

	lsdata->lsd_next = (lsrec_t *)((uintptr_t)lsrec + g_recsize);
	lsdata->lsd_count++;

	return (DTRACE_CONSUME_NEXT);
}