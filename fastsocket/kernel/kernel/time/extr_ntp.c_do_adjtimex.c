#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timex {int modes; int tick; long offset; int status; int precision; int tolerance; TYPE_1__ time; scalar_t__ stbcnt; scalar_t__ errcnt; scalar_t__ calcnt; scalar_t__ jitcnt; scalar_t__ stabil; scalar_t__ shift; scalar_t__ jitter; scalar_t__ ppsfreq; int /*<<< orphan*/  tai; int /*<<< orphan*/  constant; int /*<<< orphan*/  esterror; int /*<<< orphan*/  maxerror; void* freq; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int ADJ_ADJTIME ; 
 int ADJ_NANO ; 
 int ADJ_OFFSET_READONLY ; 
 int ADJ_OFFSET_SINGLESHOT ; 
 int ADJ_SETOFFSET ; 
 int ADJ_TICK ; 
 int /*<<< orphan*/  CAP_SYS_TIME ; 
 int EINVAL ; 
 int EPERM ; 
 int MAXFREQ_SCALED ; 
 unsigned long NSEC_PER_SEC ; 
 long NSEC_PER_USEC ; 
 int NTP_INTERVAL_FREQ ; 
 int /*<<< orphan*/  NTP_SCALE_SHIFT ; 
 int PPM_SCALE ; 
 int PPM_SCALE_INV ; 
 int PPM_SCALE_INV_SHIFT ; 
 int STA_CLOCKERR ; 
 int STA_NANO ; 
 int STA_UNSYNC ; 
 int TIME_ERROR ; 
 int USER_HZ ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 int /*<<< orphan*/  notify_cmos_timer () ; 
 int /*<<< orphan*/  ntp_lock ; 
 int /*<<< orphan*/  ntp_update_frequency () ; 
 int /*<<< orphan*/  process_adjtimex_modes (struct timex*,struct timespec*) ; 
 void* shift_right (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int tick_usec ; 
 long time_adjust ; 
 int /*<<< orphan*/  time_constant ; 
 int /*<<< orphan*/  time_esterror ; 
 int time_freq ; 
 int /*<<< orphan*/  time_maxerror ; 
 int time_offset ; 
 int time_state ; 
 int time_status ; 
 int /*<<< orphan*/  time_tai ; 
 int /*<<< orphan*/  timekeeping_inject_offset (struct timespec*) ; 

int do_adjtimex(struct timex *txc)
{
	struct timespec ts;
	int result;

	/* Validate the data before disabling interrupts */
	if (txc->modes & ADJ_ADJTIME) {
		/* singleshot must not be used with any other mode bits */
		if (!(txc->modes & ADJ_OFFSET_SINGLESHOT))
			return -EINVAL;
		if (!(txc->modes & ADJ_OFFSET_READONLY) &&
		    !capable(CAP_SYS_TIME))
			return -EPERM;
	} else {
		/* In order to modify anything, you gotta be super-user! */
		 if (txc->modes && !capable(CAP_SYS_TIME))
			return -EPERM;

		/*
		 * if the quartz is off by more than 10% then
		 * something is VERY wrong!
		 */
		if (txc->modes & ADJ_TICK &&
		    (txc->tick <  900000/USER_HZ ||
		     txc->tick > 1100000/USER_HZ))
			return -EINVAL;
	}

	if (txc->modes & ADJ_SETOFFSET) {
		struct timespec delta;
		if ((unsigned long)txc->time.tv_usec >= NSEC_PER_SEC)
			return -EINVAL;
		delta.tv_sec  = txc->time.tv_sec;
		delta.tv_nsec = txc->time.tv_usec;
		if (!capable(CAP_SYS_TIME))
			return -EPERM;
		if (!(txc->modes & ADJ_NANO))
			delta.tv_nsec *= 1000;
		timekeeping_inject_offset(&delta);
	}

	getnstimeofday(&ts);

	spin_lock_irq(&ntp_lock);

	if (txc->modes & ADJ_ADJTIME) {
		long save_adjust = time_adjust;

		if (!(txc->modes & ADJ_OFFSET_READONLY)) {
			/* adjtime() is independent from ntp_adjtime() */
			time_adjust = txc->offset;
			ntp_update_frequency();
		}
		txc->offset = save_adjust;
	} else {

		/* If there are input parameters, then process them: */
		if (txc->modes)
			process_adjtimex_modes(txc, &ts);

		txc->offset = shift_right(time_offset * NTP_INTERVAL_FREQ,
				  NTP_SCALE_SHIFT);
		if (!(time_status & STA_NANO))
			txc->offset /= NSEC_PER_USEC;
	}

	result = time_state;	/* mostly `TIME_OK' */
	if (time_status & (STA_UNSYNC|STA_CLOCKERR))
		result = TIME_ERROR;

	txc->freq	   = shift_right((time_freq >> PPM_SCALE_INV_SHIFT) *
					 PPM_SCALE_INV, NTP_SCALE_SHIFT);
	txc->maxerror	   = time_maxerror;
	txc->esterror	   = time_esterror;
	txc->status	   = time_status;
	txc->constant	   = time_constant;
	txc->precision	   = 1;
	txc->tolerance	   = MAXFREQ_SCALED / PPM_SCALE;
	txc->tick	   = tick_usec;
	txc->tai	   = time_tai;

	/* PPS is not implemented, so these are zero */
	txc->ppsfreq	   = 0;
	txc->jitter	   = 0;
	txc->shift	   = 0;
	txc->stabil	   = 0;
	txc->jitcnt	   = 0;
	txc->calcnt	   = 0;
	txc->errcnt	   = 0;
	txc->stbcnt	   = 0;

	spin_unlock_irq(&ntp_lock);

	txc->time.tv_sec = ts.tv_sec;
	txc->time.tv_usec = ts.tv_nsec;
	if (!(time_status & STA_NANO))
		txc->time.tv_usec /= NSEC_PER_USEC;

	notify_cmos_timer();

	return result;
}