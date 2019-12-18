#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dcr_cred; } ;
struct TYPE_5__ {TYPE_1__ dts_cred; } ;
typedef  TYPE_2__ dtrace_state_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_priv_proc_common_zone(dtrace_state_t *state)
{
	cred_t *cr, *s_cr = state->dts_cred.dcr_cred;
#pragma unused(cr, s_cr, state) /* __APPLE__ */

	/*
	 * We should always have a non-NULL state cred here, since if cred
	 * is null (anonymous tracing), we fast-path bypass this routine.
	 */
	ASSERT(s_cr != NULL);

	return 1; /* APPLE NOTE: Darwin doesn't do zones. */
}