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
struct TYPE_5__ {scalar_t__ pss_state; scalar_t__ pss_end_time; } ;
typedef  TYPE_1__ pool_scan_stat_t ;
struct TYPE_6__ {scalar_t__ pcs_state; scalar_t__ pcs_start_time; } ;
typedef  TYPE_2__ pool_checkpoint_stat_t ;

/* Variables and functions */
 scalar_t__ CS_CHECKPOINT_DISCARDING ; 
 scalar_t__ CS_CHECKPOINT_EXISTS ; 
 scalar_t__ CS_NONE ; 
 scalar_t__ DSS_CANCELED ; 
 scalar_t__ DSS_FINISHED ; 
 scalar_t__ DSS_NONE ; 
 scalar_t__ DSS_SCANNING ; 
 int /*<<< orphan*/  assert (int) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_checkpoint_scan_warning(pool_scan_stat_t *ps, pool_checkpoint_stat_t *pcs)
{
	if (ps == NULL || pcs == NULL)
		return;

	if (pcs->pcs_state == CS_NONE ||
	    pcs->pcs_state == CS_CHECKPOINT_DISCARDING)
		return;

	assert(pcs->pcs_state == CS_CHECKPOINT_EXISTS);

	if (ps->pss_state == DSS_NONE)
		return;

	if ((ps->pss_state == DSS_FINISHED || ps->pss_state == DSS_CANCELED) &&
	    ps->pss_end_time < pcs->pcs_start_time)
		return;

	if (ps->pss_state == DSS_FINISHED || ps->pss_state == DSS_CANCELED) {
		(void) printf(gettext("    scan warning: skipped blocks "
		    "that are only referenced by the checkpoint.\n"));
	} else {
		assert(ps->pss_state == DSS_SCANNING);
		(void) printf(gettext("    scan warning: skipping blocks "
		    "that are only referenced by the checkpoint.\n"));
	}
}