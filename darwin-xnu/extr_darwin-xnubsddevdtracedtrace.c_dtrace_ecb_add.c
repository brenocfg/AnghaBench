#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dts_necbs; scalar_t__ dts_activity; TYPE_2__** dts_ecbs; int /*<<< orphan*/  dts_epid; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_rechdr_t ;
typedef  int /*<<< orphan*/  dtrace_probe_t ;
typedef  int dtrace_epid_t ;
struct TYPE_9__ {int dte_size; int dte_needed; int dte_alignment; int dte_epid; TYPE_1__* dte_state; int /*<<< orphan*/ * dte_probe; int /*<<< orphan*/ * dte_predicate; } ;
typedef  TYPE_2__ dtrace_ecb_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_ACTIVITY_INACTIVE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  bcopy (TYPE_2__**,TYPE_2__**,int) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_membar_producer () ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__**,int) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_ecb_t *
dtrace_ecb_add(dtrace_state_t *state, dtrace_probe_t *probe)
{
	dtrace_ecb_t *ecb;
	dtrace_epid_t epid;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	ecb = kmem_zalloc(sizeof (dtrace_ecb_t), KM_SLEEP);
	ecb->dte_predicate = NULL;
	ecb->dte_probe = probe;

	/*
	 * The default size is the size of the default action: recording
	 * the header.
	 */
	ecb->dte_size = ecb->dte_needed = sizeof (dtrace_rechdr_t);
	ecb->dte_alignment = sizeof (dtrace_epid_t);

	epid = state->dts_epid++;

	if (epid - 1 >= (dtrace_epid_t)state->dts_necbs) {
		dtrace_ecb_t **oecbs = state->dts_ecbs, **ecbs;
		int necbs = state->dts_necbs << 1;

		ASSERT(epid == (dtrace_epid_t)state->dts_necbs + 1);

		if (necbs == 0) {
			ASSERT(oecbs == NULL);
			necbs = 1;
		}

		ecbs = kmem_zalloc(necbs * sizeof (*ecbs), KM_SLEEP);

		if (oecbs != NULL)
			bcopy(oecbs, ecbs, state->dts_necbs * sizeof (*ecbs));

		dtrace_membar_producer();
		state->dts_ecbs = ecbs;

		if (oecbs != NULL) {
			/*
			 * If this state is active, we must dtrace_sync()
			 * before we can free the old dts_ecbs array:  we're
			 * coming in hot, and there may be active ring
			 * buffer processing (which indexes into the dts_ecbs
			 * array) on another CPU.
			 */
			if (state->dts_activity != DTRACE_ACTIVITY_INACTIVE)
				dtrace_sync();

			kmem_free(oecbs, state->dts_necbs * sizeof (*ecbs));
		}

		dtrace_membar_producer();
		state->dts_necbs = necbs;
	}

	ecb->dte_state = state;

	ASSERT(state->dts_ecbs[epid - 1] == NULL);
	dtrace_membar_producer();
	state->dts_ecbs[(ecb->dte_epid = epid) - 1] = ecb;

	return (ecb);
}