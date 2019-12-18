#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int minor_t ;
typedef  int /*<<< orphan*/  major_t ;
struct TYPE_7__ {int dcr_visible; int dcr_action; int /*<<< orphan*/ * dcr_cred; } ;
struct TYPE_6__ {TYPE_3__* dtvs_state; } ;
struct TYPE_8__ {TYPE_2__ dts_cred; scalar_t__* dts_options; TYPE_1__ dts_vstate; void* dts_deadman; void* dts_cleaner; scalar_t__ dts_buf_over_limit; void* dts_aggbuffer; void* dts_buffer; int /*<<< orphan*/  dts_dev; int /*<<< orphan*/  dts_aggid_arena; scalar_t__ dts_epid; } ;
typedef  TYPE_3__ dtrace_state_t ;
typedef  scalar_t__ dtrace_optval_t ;
typedef  int /*<<< orphan*/  dtrace_buffer_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 void* CYCLIC_NONE ; 
 size_t DTRACEOPT_AGGRATE ; 
 size_t DTRACEOPT_BUFLIMIT ; 
 size_t DTRACEOPT_BUFPOLICY ; 
 scalar_t__ DTRACEOPT_BUFPOLICY_SWITCH ; 
 size_t DTRACEOPT_BUFRESIZE ; 
 scalar_t__ DTRACEOPT_BUFRESIZE_AUTO ; 
 size_t DTRACEOPT_CLEANRATE ; 
 size_t DTRACEOPT_CPU ; 
 size_t DTRACEOPT_JSTACKFRAMES ; 
 size_t DTRACEOPT_JSTACKSTRSIZE ; 
 int DTRACEOPT_MAX ; 
 size_t DTRACEOPT_NSPEC ; 
 size_t DTRACEOPT_SPECSIZE ; 
 size_t DTRACEOPT_STACKFRAMES ; 
 size_t DTRACEOPT_STATUSRATE ; 
 size_t DTRACEOPT_STRSIZE ; 
 size_t DTRACEOPT_SWITCHRATE ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 size_t DTRACEOPT_USTACKFRAMES ; 
 scalar_t__ DTRACE_CPUALL ; 
 void* DTRACE_CRA_ALL ; 
 int DTRACE_CRA_KERNEL ; 
 int DTRACE_CRA_PROC ; 
 int DTRACE_CRA_PROC_CONTROL ; 
 int DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER ; 
 int DTRACE_CRA_PROC_DESTRUCTIVE_ALLZONE ; 
 int DTRACE_CRA_PROC_DESTRUCTIVE_CREDCHG ; 
 void* DTRACE_CRV_ALL ; 
 int DTRACE_CRV_ALLPROC ; 
 int DTRACE_CRV_ALLZONE ; 
 int DTRACE_CRV_KERNEL ; 
 scalar_t__ DTRACE_EPIDNONE ; 
 int DTRACE_NCLIENTS ; 
 int ERESTART ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ NCPU ; 
 int /*<<< orphan*/  PRIV_ALL ; 
 int /*<<< orphan*/  PRIV_DTRACE_KERNEL ; 
 int /*<<< orphan*/  PRIV_DTRACE_PROC ; 
 int /*<<< orphan*/  PRIV_DTRACE_USER ; 
 scalar_t__ PRIV_POLICY_ONLY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_PROC_OWNER ; 
 int /*<<< orphan*/  PRIV_PROC_ZONE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int VMC_IDENTIFIER ; 
 int VM_SLEEP ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddi_driver_major (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_aggrate_default ; 
 int /*<<< orphan*/  dtrace_are_restrictions_relaxed () ; 
 scalar_t__ dtrace_buflimit_default ; 
 scalar_t__ dtrace_cleanrate_default ; 
 int /*<<< orphan*/  dtrace_devi ; 
 scalar_t__ dtrace_is_restricted () ; 
 scalar_t__ dtrace_jstackframes_default ; 
 scalar_t__ dtrace_jstackstrsize_default ; 
 int /*<<< orphan*/  dtrace_lock ; 
 scalar_t__ dtrace_nspec_default ; 
 scalar_t__ dtrace_specsize_default ; 
 scalar_t__ dtrace_stackframes_default ; 
 TYPE_3__* dtrace_state_allocate (int) ; 
 scalar_t__ dtrace_statusrate_default ; 
 scalar_t__ dtrace_strsize_default ; 
 scalar_t__ dtrace_switchrate_default ; 
 scalar_t__ dtrace_ustackframes_default ; 
 int /*<<< orphan*/  getemajor (int /*<<< orphan*/ ) ; 
 int getminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ *) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makedev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  vmem_create (char*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dtrace_state_create(dev_t *devp, cred_t *cr, dtrace_state_t **new_state)
{
	minor_t minor;
	major_t major;
	char c[30];
	dtrace_state_t *state;
	dtrace_optval_t *opt;
	int bufsize = (int)NCPU * sizeof (dtrace_buffer_t), i;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&cpu_lock, LCK_MTX_ASSERT_OWNED);

	/* Cause restart */
	*new_state = NULL;
	
	if (devp != NULL) {
		minor = getminor(*devp);
	}
	else {
		minor = DTRACE_NCLIENTS - 1;
	}

	state = dtrace_state_allocate(minor);
	if (NULL == state) {
		printf("dtrace_open: couldn't acquire minor number %d. This usually means that too many DTrace clients are in use at the moment", minor);
		return (ERESTART);	/* can't reacquire */
	}

	state->dts_epid = DTRACE_EPIDNONE + 1;

	(void) snprintf(c, sizeof (c), "dtrace_aggid_%d", minor);
	state->dts_aggid_arena = vmem_create(c, (void *)1, UINT32_MAX, 1,
	    NULL, NULL, NULL, 0, VM_SLEEP | VMC_IDENTIFIER);

	if (devp != NULL) {
		major = getemajor(*devp);
	} else {
		major = ddi_driver_major(dtrace_devi);
	}

	state->dts_dev = makedev(major, minor);

	if (devp != NULL)
		*devp = state->dts_dev;

	/*
	 * We allocate NCPU buffers.  On the one hand, this can be quite
	 * a bit of memory per instance (nearly 36K on a Starcat).  On the
	 * other hand, it saves an additional memory reference in the probe
	 * path.
	 */
	state->dts_buffer = kmem_zalloc(bufsize, KM_SLEEP);
	state->dts_aggbuffer = kmem_zalloc(bufsize, KM_SLEEP);
	state->dts_buf_over_limit = 0;
	state->dts_cleaner = CYCLIC_NONE;
	state->dts_deadman = CYCLIC_NONE;
	state->dts_vstate.dtvs_state = state;

	for (i = 0; i < DTRACEOPT_MAX; i++)
		state->dts_options[i] = DTRACEOPT_UNSET;

	/*
	 * Set the default options.
	 */
	opt = state->dts_options;
	opt[DTRACEOPT_BUFPOLICY] = DTRACEOPT_BUFPOLICY_SWITCH;
	opt[DTRACEOPT_BUFRESIZE] = DTRACEOPT_BUFRESIZE_AUTO;
	opt[DTRACEOPT_NSPEC] = dtrace_nspec_default;
	opt[DTRACEOPT_SPECSIZE] = dtrace_specsize_default;
	opt[DTRACEOPT_CPU] = (dtrace_optval_t)DTRACE_CPUALL;
	opt[DTRACEOPT_STRSIZE] = dtrace_strsize_default;
	opt[DTRACEOPT_STACKFRAMES] = dtrace_stackframes_default;
	opt[DTRACEOPT_USTACKFRAMES] = dtrace_ustackframes_default;
	opt[DTRACEOPT_CLEANRATE] = dtrace_cleanrate_default;
	opt[DTRACEOPT_AGGRATE] = dtrace_aggrate_default;
	opt[DTRACEOPT_SWITCHRATE] = dtrace_switchrate_default;
	opt[DTRACEOPT_STATUSRATE] = dtrace_statusrate_default;
	opt[DTRACEOPT_JSTACKFRAMES] = dtrace_jstackframes_default;
	opt[DTRACEOPT_JSTACKSTRSIZE] = dtrace_jstackstrsize_default;
	opt[DTRACEOPT_BUFLIMIT] = dtrace_buflimit_default;

	/*
	 * Depending on the user credentials, we set flag bits which alter probe
	 * visibility or the amount of destructiveness allowed.  In the case of
	 * actual anonymous tracing, or the possession of all privileges, all of
	 * the normal checks are bypassed.
	 */
#if defined(__APPLE__)
	if (cr != NULL) {
		kauth_cred_ref(cr);
		state->dts_cred.dcr_cred = cr;
	}
	if (cr == NULL || PRIV_POLICY_ONLY(cr, PRIV_ALL, B_FALSE)) {
		if (dtrace_is_restricted() && !dtrace_are_restrictions_relaxed()) {
			/*
			 * Allow only proc credentials when DTrace is
			 * restricted by the current security policy
			 */
			state->dts_cred.dcr_visible = DTRACE_CRV_ALLPROC;
			state->dts_cred.dcr_action = DTRACE_CRA_PROC | DTRACE_CRA_PROC_CONTROL | DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER;
		}
		else {
			state->dts_cred.dcr_visible = DTRACE_CRV_ALL;
			state->dts_cred.dcr_action = DTRACE_CRA_ALL;
		}
	}

#else
	if (cr == NULL || PRIV_POLICY_ONLY(cr, PRIV_ALL, B_FALSE)) {
		state->dts_cred.dcr_visible = DTRACE_CRV_ALL;
		state->dts_cred.dcr_action = DTRACE_CRA_ALL;
	}
	else {
		/*
		 * Set up the credentials for this instantiation.  We take a
		 * hold on the credential to prevent it from disappearing on
		 * us; this in turn prevents the zone_t referenced by this
		 * credential from disappearing.  This means that we can
		 * examine the credential and the zone from probe context.
		 */
		crhold(cr);
		state->dts_cred.dcr_cred = cr;

		/*
		 * CRA_PROC means "we have *some* privilege for dtrace" and
		 * unlocks the use of variables like pid, zonename, etc.
		 */
		if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_USER, B_FALSE) ||
		    PRIV_POLICY_ONLY(cr, PRIV_DTRACE_PROC, B_FALSE)) {
			state->dts_cred.dcr_action |= DTRACE_CRA_PROC;
		}

		/*
		 * dtrace_user allows use of syscall and profile providers.
		 * If the user also has proc_owner and/or proc_zone, we
		 * extend the scope to include additional visibility and
		 * destructive power.
		 */
		if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_USER, B_FALSE)) {
			if (PRIV_POLICY_ONLY(cr, PRIV_PROC_OWNER, B_FALSE)) {
				state->dts_cred.dcr_visible |=
				    DTRACE_CRV_ALLPROC;

				state->dts_cred.dcr_action |=
				    DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER;
			}

			if (PRIV_POLICY_ONLY(cr, PRIV_PROC_ZONE, B_FALSE)) {
				state->dts_cred.dcr_visible |=
				    DTRACE_CRV_ALLZONE;

				state->dts_cred.dcr_action |=
				    DTRACE_CRA_PROC_DESTRUCTIVE_ALLZONE;
			}

			/*
			 * If we have all privs in whatever zone this is,
			 * we can do destructive things to processes which
			 * have altered credentials.
			 *
			 * APPLE NOTE: Darwin doesn't do zones.
			 * Behave as if zone always has destructive privs.
			 */

			state->dts_cred.dcr_action |=
				DTRACE_CRA_PROC_DESTRUCTIVE_CREDCHG;
		}

		/*
		 * Holding the dtrace_kernel privilege also implies that
		 * the user has the dtrace_user privilege from a visibility
		 * perspective.  But without further privileges, some
		 * destructive actions are not available.
		 */
		if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_KERNEL, B_FALSE)) {
			/*
			 * Make all probes in all zones visible.  However,
			 * this doesn't mean that all actions become available
			 * to all zones.
			 */
			state->dts_cred.dcr_visible |= DTRACE_CRV_KERNEL |
			    DTRACE_CRV_ALLPROC | DTRACE_CRV_ALLZONE;

			state->dts_cred.dcr_action |= DTRACE_CRA_KERNEL |
			    DTRACE_CRA_PROC;
			/*
			 * Holding proc_owner means that destructive actions
			 * for *this* zone are allowed.
			 */
			if (PRIV_POLICY_ONLY(cr, PRIV_PROC_OWNER, B_FALSE))
				state->dts_cred.dcr_action |=
				    DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER;

			/*
			 * Holding proc_zone means that destructive actions
			 * for this user/group ID in all zones is allowed.
			 */
			if (PRIV_POLICY_ONLY(cr, PRIV_PROC_ZONE, B_FALSE))
				state->dts_cred.dcr_action |=
				    DTRACE_CRA_PROC_DESTRUCTIVE_ALLZONE;

			/*
			 * If we have all privs in whatever zone this is,
			 * we can do destructive things to processes which
			 * have altered credentials.
			 *
			 * APPLE NOTE: Darwin doesn't do zones.			 
			 * Behave as if zone always has destructive privs.
			 */			
			state->dts_cred.dcr_action |=
				DTRACE_CRA_PROC_DESTRUCTIVE_CREDCHG;
		}

		/*
		 * Holding the dtrace_proc privilege gives control over fasttrap
		 * and pid providers.  We need to grant wider destructive
		 * privileges in the event that the user has proc_owner and/or
		 * proc_zone.
		 */
		if (PRIV_POLICY_ONLY(cr, PRIV_DTRACE_PROC, B_FALSE)) {
			if (PRIV_POLICY_ONLY(cr, PRIV_PROC_OWNER, B_FALSE))
				state->dts_cred.dcr_action |=
				    DTRACE_CRA_PROC_DESTRUCTIVE_ALLUSER;

			if (PRIV_POLICY_ONLY(cr, PRIV_PROC_ZONE, B_FALSE))
				state->dts_cred.dcr_action |=
				    DTRACE_CRA_PROC_DESTRUCTIVE_ALLZONE;
		}
	}
#endif

	*new_state = state;
	return(0);  /* Success */
}