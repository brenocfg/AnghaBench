#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ (* dmc_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dmc_data; } ;
typedef  TYPE_1__ dtrace_match_cond_t ;
struct TYPE_9__ {int dten_ndesc; int dten_error; TYPE_3__* dten_current; TYPE_3__** dten_desc; } ;
typedef  TYPE_2__ dtrace_enabling_t ;
struct TYPE_10__ {int /*<<< orphan*/  dted_probegen; int /*<<< orphan*/  dted_probe; } ;
typedef  TYPE_3__ dtrace_ecbdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_WARN ; 
 int EBUSY ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,void*,int) ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_probe_enable (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_probegen ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_enabling_match(dtrace_enabling_t *enab, int *nmatched, dtrace_match_cond_t *cond)
{
	int i = 0;
	int total_matched = 0, matched = 0;

	LCK_MTX_ASSERT(&cpu_lock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	for (i = 0; i < enab->dten_ndesc; i++) {
		dtrace_ecbdesc_t *ep = enab->dten_desc[i];

		enab->dten_current = ep;
		enab->dten_error = 0;

		/**
		 * Before doing a dtrace_probe_enable, which is really
		 * expensive, check that this enabling matches the matching precondition
		 * if we have one
		 */
		if (cond && (cond->dmc_func(&ep->dted_probe, cond->dmc_data) == 0)) {
			continue;
		}
		/*
		 * If a provider failed to enable a probe then get out and
		 * let the consumer know we failed.
		 */
		if ((matched = dtrace_probe_enable(&ep->dted_probe, enab, ep)) < 0)
			return (EBUSY);

		total_matched += matched;

		if (enab->dten_error != 0) {
			/*
			 * If we get an error half-way through enabling the
			 * probes, we kick out -- perhaps with some number of
			 * them enabled.  Leaving enabled probes enabled may
			 * be slightly confusing for user-level, but we expect
			 * that no one will attempt to actually drive on in
			 * the face of such errors.  If this is an anonymous
			 * enabling (indicated with a NULL nmatched pointer),
			 * we cmn_err() a message.  We aren't expecting to
			 * get such an error -- such as it can exist at all,
			 * it would be a result of corrupted DOF in the driver
			 * properties.
			 */
			if (nmatched == NULL) {
				cmn_err(CE_WARN, "dtrace_enabling_match() "
				    "error on %p: %d", (void *)ep,
				    enab->dten_error);
			}

			return (enab->dten_error);
		}

		ep->dted_probegen = dtrace_probegen;
	}

	if (nmatched != NULL)
		*nmatched = total_matched;

	return (0);
}