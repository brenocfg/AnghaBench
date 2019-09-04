#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  user_ntv ;
struct user64_timex {unsigned int modes; int offset; long long freq; int status; scalar_t__ constant; int precision; long tolerance; void* esterror; void* maxerror; } ;
struct user32_timex {unsigned int modes; int offset; long long freq; int status; scalar_t__ constant; int precision; long tolerance; void* esterror; void* maxerror; } ;
struct timex {unsigned int modes; int offset; long long freq; int status; scalar_t__ constant; int precision; long tolerance; void* esterror; void* maxerror; } ;
struct proc {int dummy; } ;
struct ntp_adjtime_args {int /*<<< orphan*/  tp; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  clock_usec_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOTaskHasEntitlement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 int L_GINT (long long) ; 
 int /*<<< orphan*/  L_LINT (long long,long) ; 
 long MAXFREQ ; 
 scalar_t__ MAXTC ; 
 unsigned int MOD_CLKA ; 
 unsigned int MOD_CLKB ; 
 unsigned int MOD_ESTERROR ; 
 unsigned int MOD_FREQUENCY ; 
 unsigned int MOD_MAXERROR ; 
 unsigned int MOD_MICRO ; 
 unsigned int MOD_NANO ; 
 unsigned int MOD_OFFSET ; 
 unsigned int MOD_STATUS ; 
 unsigned int MOD_TAI ; 
 unsigned int MOD_TIMECONST ; 
 int /*<<< orphan*/  NTP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_ADJTIME ; 
 long SCALE_PPM ; 
 int /*<<< orphan*/  SETTIME_ENTITLEMENT ; 
 int STA_CLK ; 
 int STA_NANO ; 
 int STA_PLL ; 
 int STA_RONLY ; 
 int STA_SUPPORTED ; 
 int STA_UNSYNC ; 
 int TIME_ERROR ; 
 int TIME_OK ; 
 int /*<<< orphan*/  clock_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int copyin (int /*<<< orphan*/ ,struct user64_timex*,int) ; 
 int copyout (struct user64_timex*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  hardupdate (int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  last_time_maxerror_update ; 
 scalar_t__ ntp_is_time_error (int) ; 
 int priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_ntp_loop () ; 
 void* time_constant ; 
 void* time_esterror ; 
 long long time_freq ; 
 void* time_maxerror ; 
 long long time_offset ; 
 int time_precision ; 
 int time_state ; 
 int time_status ; 
 scalar_t__ time_tai ; 

int
ntp_adjtime(struct proc *p, struct ntp_adjtime_args *uap, int32_t *retval)
{
	struct timex ntv = {};
	long freq;
	unsigned int modes;
	int error, ret = 0;
	clock_sec_t sec;
	clock_usec_t microsecs;
	boolean_t enable;

	if (IS_64BIT_PROCESS(p)) {
		struct user64_timex user_ntv;
		error = copyin(uap->tp, &user_ntv, sizeof(user_ntv));
		ntv.modes = user_ntv.modes;
		ntv.offset = user_ntv.offset;
		ntv.freq = user_ntv.freq;
		ntv.maxerror = user_ntv.maxerror;
		ntv.esterror = user_ntv.esterror;
		ntv.status = user_ntv.status;
		ntv.constant = user_ntv.constant;
		ntv.precision = user_ntv.precision;
		ntv.tolerance = user_ntv.tolerance;

	} else {
		struct user32_timex user_ntv;
		error = copyin(uap->tp, &user_ntv, sizeof(user_ntv));
		ntv.modes = user_ntv.modes;
		ntv.offset = user_ntv.offset;
		ntv.freq = user_ntv.freq;
		ntv.maxerror = user_ntv.maxerror;
		ntv.esterror = user_ntv.esterror;
		ntv.status = user_ntv.status;
		ntv.constant = user_ntv.constant;
		ntv.precision = user_ntv.precision;
		ntv.tolerance = user_ntv.tolerance;
	}
	if (error)
		return (error);

#if DEVELOPEMNT || DEBUG
	if (g_should_log_clock_adjustments) {
		os_log(OS_LOG_DEFAULT, "%s: BEFORE modes %u offset %ld freq %ld status %d constant %ld time_adjtime %lld\n",
		       __func__, ntv.modes, ntv.offset, ntv.freq, ntv.status, ntv.constant, time_adjtime);
	}
#endif
	/*
	 * Update selected clock variables - only the superuser can
	 * change anything. Note that there is no error checking here on
	 * the assumption the superuser should know what it is doing.
	 * Note that either the time constant or TAI offset are loaded
	 * from the ntv.constant member, depending on the mode bits. If
	 * the STA_PLL bit in the status word is cleared, the state and
	 * status words are reset to the initial values at boot.
	 */
	modes = ntv.modes;
	if (modes) {
		/* Check that this task is entitled to set the time or it is root */
		if (!IOTaskHasEntitlement(current_task(), SETTIME_ENTITLEMENT)) {
#if CONFIG_MACF
			error = mac_system_check_settime(kauth_cred_get());
			if (error)
				return (error);
#endif
			if ((error = priv_check_cred(kauth_cred_get(), PRIV_ADJTIME, 0)))
				return (error);

		}
	}

	NTP_LOCK(enable);

	if (modes & MOD_MAXERROR) {
		clock_gettimeofday(&sec, &microsecs);
		time_maxerror = ntv.maxerror;
		last_time_maxerror_update = sec;
	}
	if (modes & MOD_ESTERROR)
		time_esterror = ntv.esterror;
	if (modes & MOD_STATUS) {
		if (time_status & STA_PLL && !(ntv.status & STA_PLL)) {
			time_state = TIME_OK;
			time_status = STA_UNSYNC;
		}
		time_status &= STA_RONLY;
		time_status |= ntv.status & ~STA_RONLY;
		/*
		 * Nor PPS or leaps seconds are supported.
		 * Filter out unsupported bits.
		 */
		time_status &= STA_SUPPORTED;
	}
	if (modes & MOD_TIMECONST) {
		if (ntv.constant < 0)
			time_constant = 0;
		else if (ntv.constant > MAXTC)
			time_constant = MAXTC;
		else
			time_constant = ntv.constant;
	}
	if (modes & MOD_TAI) {
		if (ntv.constant > 0)
			time_tai = ntv.constant;
	}
	if (modes & MOD_NANO)
		time_status |= STA_NANO;
	if (modes & MOD_MICRO)
		time_status &= ~STA_NANO;
	if (modes & MOD_CLKB)
		time_status |= STA_CLK;
	if (modes & MOD_CLKA)
		time_status &= ~STA_CLK;
	if (modes & MOD_FREQUENCY) {
		freq = (ntv.freq * 1000LL) >> 16;
		if (freq > MAXFREQ)
			L_LINT(time_freq, MAXFREQ);
		else if (freq < -MAXFREQ)
			L_LINT(time_freq, -MAXFREQ);
		else {
			/*
			 * ntv.freq is [PPM * 2^16] = [us/s * 2^16]
			 * time_freq is [ns/s * 2^32]
			 */
			time_freq = ntv.freq * 1000LL * 65536LL;
		}
	}
	if (modes & MOD_OFFSET) {
		if (time_status & STA_NANO)
			hardupdate(ntv.offset);
		else
			hardupdate(ntv.offset * 1000);
	}

	ret = ntp_is_time_error(time_status) ? TIME_ERROR : time_state;

#if DEVELOPEMNT || DEBUG
	if (g_should_log_clock_adjustments) {
		os_log(OS_LOG_DEFAULT, "%s: AFTER modes %u offset %lld freq %lld status %d constant %ld time_adjtime %lld\n",
		       __func__, modes, time_offset, time_freq, time_status, time_constant, time_adjtime);
	}
#endif

	/*
	 * Retrieve all clock variables. Note that the TAI offset is
	 * returned only by ntp_gettime();
	 */
	if (IS_64BIT_PROCESS(p)) {
		struct user64_timex user_ntv = {};

		user_ntv.modes = modes;
		if (time_status & STA_NANO)
			user_ntv.offset = L_GINT(time_offset);
		else
			user_ntv.offset = L_GINT(time_offset) / 1000;
		user_ntv.freq = L_GINT((time_freq / 1000LL) << 16);
		user_ntv.maxerror = time_maxerror;
		user_ntv.esterror = time_esterror;
		user_ntv.status = time_status;
		user_ntv.constant = time_constant;
		if (time_status & STA_NANO)
			user_ntv.precision = time_precision;
		else
			user_ntv.precision = time_precision / 1000;
		user_ntv.tolerance = MAXFREQ * SCALE_PPM;

		/* unlock before copyout */
		NTP_UNLOCK(enable);

		error = copyout(&user_ntv, uap->tp, sizeof(user_ntv));

	}
	else{
		struct user32_timex user_ntv = {};

		user_ntv.modes = modes;
		if (time_status & STA_NANO)
			user_ntv.offset = L_GINT(time_offset);
		else
			user_ntv.offset = L_GINT(time_offset) / 1000;
		user_ntv.freq = L_GINT((time_freq / 1000LL) << 16);
		user_ntv.maxerror = time_maxerror;
		user_ntv.esterror = time_esterror;
		user_ntv.status = time_status;
		user_ntv.constant = time_constant;
		if (time_status & STA_NANO)
			user_ntv.precision = time_precision;
		else
			user_ntv.precision = time_precision / 1000;
		user_ntv.tolerance = MAXFREQ * SCALE_PPM;

		/* unlock before copyout */
		NTP_UNLOCK(enable);

		error = copyout(&user_ntv, uap->tp, sizeof(user_ntv));
	}

	if (modes)
		start_ntp_loop();

	if (error == 0)
		*retval = ret;

	return (error);
}