#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_2__* uthread_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * thread_t ;
typedef  void* pc_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_24__ {int dts_arg_error_illval; int /*<<< orphan*/  dts_vstate; } ;
typedef  TYPE_3__ dtrace_state_t ;
struct TYPE_22__ {int (* dtps_getargval ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_25__ {int /*<<< orphan*/  dtpv_name; int /*<<< orphan*/  dtpv_arg; TYPE_1__ dtpv_pops; } ;
typedef  TYPE_4__ dtrace_provider_t ;
struct TYPE_26__ {int dtms_present; int* dtms_arg; int dtms_timestamp; int dtms_walltimestamp; int dtms_machtimestamp; int dtms_ipl; int dtms_epid; int dtms_stackdepth; int dtms_ustackdepth; uintptr_t dtms_caller; int dtms_ucaller; size_t dtms_scratch_ptr; TYPE_16__* dtms_probe; } ;
typedef  TYPE_5__ dtrace_mstate_t ;
struct TYPE_23__ {int /*<<< orphan*/  t_dtrace_errno; } ;
struct TYPE_21__ {size_t cpu_id; } ;
struct TYPE_20__ {int dtpr_id; int /*<<< orphan*/  dtpr_name; int /*<<< orphan*/  dtpr_func; int /*<<< orphan*/  dtpr_mod; TYPE_4__* dtpr_provider; int /*<<< orphan*/  dtpr_aframes; int /*<<< orphan*/  dtpr_arg; } ;
struct TYPE_19__ {int /*<<< orphan*/  cpuc_dtrace_illval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_17__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_BADADDR ; 
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  CPU_DTRACE_NOFAULT ; 
 int /*<<< orphan*/  CPU_DTRACE_NOSCRATCH ; 
 int /*<<< orphan*/  CPU_ON_INTR (TYPE_17__*) ; 
 int DIF_VAR_ARG0 ; 
 int DIF_VAR_ARG9 ; 
#define  DIF_VAR_ARGS 160 
#define  DIF_VAR_CALLER 159 
#define  DIF_VAR_CPU 158 
#define  DIF_VAR_CPUCYCLES 157 
#define  DIF_VAR_CPUINSTRS 156 
#define  DIF_VAR_CURTHREAD 155 
#define  DIF_VAR_DISPATCHQADDR 154 
#define  DIF_VAR_EPID 153 
#define  DIF_VAR_ERRNO 152 
#define  DIF_VAR_EXECNAME 151 
#define  DIF_VAR_GID 150 
#define  DIF_VAR_ID 149 
#define  DIF_VAR_IPL 148 
#define  DIF_VAR_MACHTIMESTAMP 147 
#define  DIF_VAR_PID 146 
#define  DIF_VAR_PPID 145 
#define  DIF_VAR_PROBEFUNC 144 
#define  DIF_VAR_PROBEMOD 143 
#define  DIF_VAR_PROBENAME 142 
#define  DIF_VAR_PROBEPROV 141 
#define  DIF_VAR_PTHREAD_SELF 140 
#define  DIF_VAR_STACKDEPTH 139 
#define  DIF_VAR_TID 138 
#define  DIF_VAR_TIMESTAMP 137 
#define  DIF_VAR_UCALLER 136 
#define  DIF_VAR_UID 135 
#define  DIF_VAR_UREGS 134 
#define  DIF_VAR_USTACKDEPTH 133 
#define  DIF_VAR_VCYCLES 132 
#define  DIF_VAR_VINSTRS 131 
#define  DIF_VAR_VTIMESTAMP 130 
#define  DIF_VAR_WALLTIMESTAMP 129 
#define  DIF_VAR_ZONENAME 128 
 int /*<<< orphan*/  DTRACE_ANCHORED (TYPE_16__*) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_INSCRATCH (TYPE_5__*,size_t) ; 
 int DTRACE_MSTATE_ARGS ; 
 int DTRACE_MSTATE_CALLER ; 
 int DTRACE_MSTATE_EPID ; 
 int DTRACE_MSTATE_IPL ; 
 int DTRACE_MSTATE_MACHTIMESTAMP ; 
 int DTRACE_MSTATE_PROBE ; 
 int DTRACE_MSTATE_STACKDEPTH ; 
 int DTRACE_MSTATE_TIMESTAMP ; 
 int DTRACE_MSTATE_UCALLER ; 
 int DTRACE_MSTATE_USTACKDEPTH ; 
 int DTRACE_MSTATE_WALLTIMESTAMP ; 
 int /*<<< orphan*/  MAXCOMLEN ; 
 TYPE_14__* cpu_core ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/ * dtrace_CRED () ; 
 uintptr_t dtrace_caller (int) ; 
 int dtrace_dif_varstr (uintptr_t,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dtrace_get_thread_last_cpu_id (int /*<<< orphan*/ *) ; 
 int dtrace_get_thread_vtime (int /*<<< orphan*/ *) ; 
 int dtrace_getarg (int,int,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int dtrace_gethrestime () ; 
 int dtrace_gethrtime () ; 
 int dtrace_getipl () ; 
 int /*<<< orphan*/  dtrace_getpcstack (void**,int,int,int /*<<< orphan*/ *) ; 
 int dtrace_getreg (int /*<<< orphan*/ ,int) ; 
 int dtrace_getstackdepth (int) ; 
 int /*<<< orphan*/  dtrace_getupcstack (int*,int) ; 
 int dtrace_getustackdepth () ; 
 int /*<<< orphan*/  dtrace_priv_kernel (TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_priv_proc (TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_priv_proc_relaxed (TYPE_3__*) ; 
 int dtrace_probeid_error ; 
 int /*<<< orphan*/  dtrace_proc_selfpid () ; 
 int /*<<< orphan*/  dtrace_proc_selfppid () ; 
 int /*<<< orphan*/  dtrace_proc_selfruid () ; 
 int /*<<< orphan*/  dtrace_vtime_references ; 
 int /*<<< orphan*/  find_user_regs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_getgid () ; 
 int mach_absolute_time () ; 
 int mt_cur_cpu_cycles () ; 
 int mt_cur_cpu_instrs () ; 
 int mt_cur_thread_cycles () ; 
 int mt_cur_thread_instrs () ; 
 int /*<<< orphan*/  proc_selfname (char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int thread_dispatchqaddr (int /*<<< orphan*/ *) ; 
 int thread_tid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
dtrace_dif_variable(dtrace_mstate_t *mstate, dtrace_state_t *state, uint64_t v,
    uint64_t ndx)
{
	/*
	 * If we're accessing one of the uncached arguments, we'll turn this
	 * into a reference in the args array.
	 */
	if (v >= DIF_VAR_ARG0 && v <= DIF_VAR_ARG9) {
		ndx = v - DIF_VAR_ARG0;
		v = DIF_VAR_ARGS;
	}

	switch (v) {
	case DIF_VAR_ARGS:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_ARGS);
		if (ndx >= sizeof (mstate->dtms_arg) /
		    sizeof (mstate->dtms_arg[0])) {
			/*
			 * APPLE NOTE: Account for introduction of __dtrace_probe()
			 */
			int aframes = mstate->dtms_probe->dtpr_aframes + 3;
			dtrace_vstate_t *vstate = &state->dts_vstate;
			dtrace_provider_t *pv;
			uint64_t val;

			pv = mstate->dtms_probe->dtpr_provider;
			if (pv->dtpv_pops.dtps_getargval != NULL)
				val = pv->dtpv_pops.dtps_getargval(pv->dtpv_arg,
				    mstate->dtms_probe->dtpr_id,
				    mstate->dtms_probe->dtpr_arg, ndx, aframes);
			/* Special case access of arg5 as passed to dtrace_probe_error() (which see.) */
			else if (mstate->dtms_probe->dtpr_id == dtrace_probeid_error && ndx == 5) {
			        return ((dtrace_state_t *)(uintptr_t)(mstate->dtms_arg[0]))->dts_arg_error_illval;
			}

			else
				val = dtrace_getarg(ndx, aframes, mstate, vstate);

			/*
			 * This is regrettably required to keep the compiler
			 * from tail-optimizing the call to dtrace_getarg().
			 * The condition always evaluates to true, but the
			 * compiler has no way of figuring that out a priori.
			 * (None of this would be necessary if the compiler
			 * could be relied upon to _always_ tail-optimize
			 * the call to dtrace_getarg() -- but it can't.)
			 */
			if (mstate->dtms_probe != NULL)
				return (val);

			ASSERT(0);
		}

		return (mstate->dtms_arg[ndx]);

	case DIF_VAR_UREGS: {
		thread_t thread;

		if (!dtrace_priv_proc(state))
			return (0);

		if ((thread = current_thread()) == NULL) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_BADADDR);
			cpu_core[CPU->cpu_id].cpuc_dtrace_illval = 0;
			return (0);
		}

		return (dtrace_getreg(find_user_regs(thread), ndx));
	}


	case DIF_VAR_CURTHREAD:
		if (!dtrace_priv_kernel(state))
			return (0);

		return ((uint64_t)(uintptr_t)current_thread());

	case DIF_VAR_TIMESTAMP:
		if (!(mstate->dtms_present & DTRACE_MSTATE_TIMESTAMP)) {
			mstate->dtms_timestamp = dtrace_gethrtime();
			mstate->dtms_present |= DTRACE_MSTATE_TIMESTAMP;
		}
		return (mstate->dtms_timestamp);

	case DIF_VAR_VTIMESTAMP:
		ASSERT(dtrace_vtime_references != 0);
		return (dtrace_get_thread_vtime(current_thread()));

	case DIF_VAR_WALLTIMESTAMP:
		if (!(mstate->dtms_present & DTRACE_MSTATE_WALLTIMESTAMP)) {
			mstate->dtms_walltimestamp = dtrace_gethrestime();
			mstate->dtms_present |= DTRACE_MSTATE_WALLTIMESTAMP;
		}
		return (mstate->dtms_walltimestamp);

	case DIF_VAR_MACHTIMESTAMP:
		if (!(mstate->dtms_present & DTRACE_MSTATE_MACHTIMESTAMP)) {
			mstate->dtms_machtimestamp = mach_absolute_time();
			mstate->dtms_present |= DTRACE_MSTATE_MACHTIMESTAMP;
		}
		return (mstate->dtms_machtimestamp);

	case DIF_VAR_CPU:
		return ((uint64_t) dtrace_get_thread_last_cpu_id(current_thread()));

	case DIF_VAR_IPL:
		if (!dtrace_priv_kernel(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_IPL)) {
			mstate->dtms_ipl = dtrace_getipl();
			mstate->dtms_present |= DTRACE_MSTATE_IPL;
		}
		return (mstate->dtms_ipl);

	case DIF_VAR_EPID:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_EPID);
		return (mstate->dtms_epid);

	case DIF_VAR_ID:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (mstate->dtms_probe->dtpr_id);

	case DIF_VAR_STACKDEPTH:
		if (!dtrace_priv_kernel(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_STACKDEPTH)) {
			/*
			 * APPLE NOTE: Account for introduction of __dtrace_probe()
			 */
			int aframes = mstate->dtms_probe->dtpr_aframes + 3;

			mstate->dtms_stackdepth = dtrace_getstackdepth(aframes);
			mstate->dtms_present |= DTRACE_MSTATE_STACKDEPTH;
		}
		return (mstate->dtms_stackdepth);

	case DIF_VAR_USTACKDEPTH:
		if (!dtrace_priv_proc(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_USTACKDEPTH)) {
			/*
			 * See comment in DIF_VAR_PID.
			 */
			if (DTRACE_ANCHORED(mstate->dtms_probe) &&
			    CPU_ON_INTR(CPU)) {
				mstate->dtms_ustackdepth = 0;
			} else {
				DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
				mstate->dtms_ustackdepth =
				    dtrace_getustackdepth();
				DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
			}
			mstate->dtms_present |= DTRACE_MSTATE_USTACKDEPTH;
		}
		return (mstate->dtms_ustackdepth);

	case DIF_VAR_CALLER:
		if (!dtrace_priv_kernel(state))
			return (0);
		if (!(mstate->dtms_present & DTRACE_MSTATE_CALLER)) {
			/*
			 * APPLE NOTE: Account for introduction of __dtrace_probe()
			 */
			int aframes = mstate->dtms_probe->dtpr_aframes + 3;

			if (!DTRACE_ANCHORED(mstate->dtms_probe)) {
				/*
				 * If this is an unanchored probe, we are
				 * required to go through the slow path:
				 * dtrace_caller() only guarantees correct
				 * results for anchored probes.
				 */
				pc_t caller[2];

				dtrace_getpcstack(caller, 2, aframes,
				    (uint32_t *)(uintptr_t)mstate->dtms_arg[0]);
				mstate->dtms_caller = caller[1];
			} else if ((mstate->dtms_caller =
				dtrace_caller(aframes)) == (uintptr_t)-1) {
				/*
				 * We have failed to do this the quick way;
				 * we must resort to the slower approach of
				 * calling dtrace_getpcstack().
				 */
				pc_t caller;

				dtrace_getpcstack(&caller, 1, aframes, NULL);
				mstate->dtms_caller = caller;
			}

			mstate->dtms_present |= DTRACE_MSTATE_CALLER;
		}
		return (mstate->dtms_caller);

	case DIF_VAR_UCALLER:
		if (!dtrace_priv_proc(state))
			return (0);

		if (!(mstate->dtms_present & DTRACE_MSTATE_UCALLER)) {
			uint64_t ustack[3];

			/*
			 * dtrace_getupcstack() fills in the first uint64_t
			 * with the current PID.  The second uint64_t will
			 * be the program counter at user-level.  The third
			 * uint64_t will contain the caller, which is what
			 * we're after.
			 */
			ustack[2] = 0;
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
			dtrace_getupcstack(ustack, 3);
			DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
			mstate->dtms_ucaller = ustack[2];
			mstate->dtms_present |= DTRACE_MSTATE_UCALLER;
		}

		return (mstate->dtms_ucaller);

	case DIF_VAR_PROBEPROV:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_provider->dtpv_name,
		    state, mstate));

	case DIF_VAR_PROBEMOD:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_mod,
		    state, mstate));

	case DIF_VAR_PROBEFUNC:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_func,
		    state, mstate));

	case DIF_VAR_PROBENAME:
		ASSERT(mstate->dtms_present & DTRACE_MSTATE_PROBE);
		return (dtrace_dif_varstr(
		    (uintptr_t)mstate->dtms_probe->dtpr_name,
		    state, mstate));

	case DIF_VAR_PID:
		if (!dtrace_priv_proc_relaxed(state))
			return (0);

		/*
		 * Note that we are assuming that an unanchored probe is
		 * always due to a high-level interrupt.  (And we're assuming
		 * that there is only a single high level interrupt.)
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			/* Anchored probe that fires while on an interrupt accrues to process 0 */
			return 0; 

		return ((uint64_t)dtrace_proc_selfpid());

	case DIF_VAR_PPID:
		if (!dtrace_priv_proc_relaxed(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (0);

		return ((uint64_t)dtrace_proc_selfppid());

	case DIF_VAR_TID:
		/* We do not need to check for null current_thread() */
		return thread_tid(current_thread()); /* globally unique */

	case DIF_VAR_PTHREAD_SELF:
		if (!dtrace_priv_proc(state))
			return (0);

		/* Not currently supported, but we should be able to delta the dispatchqaddr and dispatchqoffset to get pthread_self */
		return 0;

	case DIF_VAR_DISPATCHQADDR:
		if (!dtrace_priv_proc(state))
			return (0);

		/* We do not need to check for null current_thread() */
		return thread_dispatchqaddr(current_thread());

	case DIF_VAR_EXECNAME:
	{
		char *xname = (char *)mstate->dtms_scratch_ptr;
		size_t scratch_size = MAXCOMLEN+1;
		
		/* The scratch allocation's lifetime is that of the clause. */
		if (!DTRACE_INSCRATCH(mstate, scratch_size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			return 0;
		}
			
		if (!dtrace_priv_proc_relaxed(state))
			return (0);

		mstate->dtms_scratch_ptr += scratch_size;
		proc_selfname( xname, scratch_size );

		return ((uint64_t)(uintptr_t)xname);
	}


	case DIF_VAR_ZONENAME:
	{
		/* scratch_size is equal to length('global') + 1 for the null-terminator. */
		char *zname = (char *)mstate->dtms_scratch_ptr;
		size_t scratch_size = 6 + 1;

		if (!dtrace_priv_proc(state))
			return (0);

		/* The scratch allocation's lifetime is that of the clause. */
		if (!DTRACE_INSCRATCH(mstate, scratch_size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			return 0;
		}

		mstate->dtms_scratch_ptr += scratch_size;

		/* The kernel does not provide zonename, it will always return 'global'. */
		strlcpy(zname, "global", scratch_size);

		return ((uint64_t)(uintptr_t)zname);
	}

#if MONOTONIC
	case DIF_VAR_CPUINSTRS:
		return mt_cur_cpu_instrs();

	case DIF_VAR_CPUCYCLES:
		return mt_cur_cpu_cycles();

	case DIF_VAR_VINSTRS:
		return mt_cur_thread_instrs();

	case DIF_VAR_VCYCLES:
		return mt_cur_thread_cycles();
#else /* MONOTONIC */
	case DIF_VAR_CPUINSTRS: /* FALLTHROUGH */
	case DIF_VAR_CPUCYCLES: /* FALLTHROUGH */
	case DIF_VAR_VINSTRS: /* FALLTHROUGH */
	case DIF_VAR_VCYCLES: /* FALLTHROUGH */
		return 0;
#endif /* !MONOTONIC */

	case DIF_VAR_UID:
		if (!dtrace_priv_proc_relaxed(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (0);

		return ((uint64_t) dtrace_proc_selfruid());

	case DIF_VAR_GID:
		if (!dtrace_priv_proc(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (0);

		if (dtrace_CRED() != NULL)
			/* Credential does not require lazy initialization. */
			return ((uint64_t)kauth_getgid());
		else {
			/* proc_lock would be taken under kauth_cred_proc_ref() in kauth_cred_get(). */
			DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
			return -1ULL;
		}

	case DIF_VAR_ERRNO: {
		uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());
		if (!dtrace_priv_proc(state))
			return (0);

		/*
		 * See comment in DIF_VAR_PID.
		 */
		if (DTRACE_ANCHORED(mstate->dtms_probe) && CPU_ON_INTR(CPU))
			return (0);

		if (uthread)
			return (uint64_t)uthread->t_dtrace_errno;
		else {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
			return -1ULL;
		}
	}

	default:
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}
}