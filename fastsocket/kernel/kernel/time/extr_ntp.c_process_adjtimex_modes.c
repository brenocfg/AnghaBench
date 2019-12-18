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
struct timex {int modes; int freq; int constant; int /*<<< orphan*/  tick; int /*<<< orphan*/  offset; int /*<<< orphan*/  esterror; int /*<<< orphan*/  maxerror; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int ADJ_ESTERROR ; 
 int ADJ_FREQUENCY ; 
 int ADJ_MAXERROR ; 
 int ADJ_MICRO ; 
 int ADJ_NANO ; 
 int ADJ_OFFSET ; 
 int ADJ_STATUS ; 
 int ADJ_TAI ; 
 int ADJ_TICK ; 
 int ADJ_TIMECONST ; 
 long MAXFREQ_SCALED ; 
 scalar_t__ MAXTC ; 
 int PPM_SCALE ; 
 int STA_NANO ; 
 int max (int,long) ; 
 int min (int,long) ; 
 int /*<<< orphan*/  ntp_update_frequency () ; 
 int /*<<< orphan*/  ntp_update_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_adj_status (struct timex*,struct timespec*) ; 
 int /*<<< orphan*/  tick_usec ; 
 int time_constant ; 
 int /*<<< orphan*/  time_esterror ; 
 int time_freq ; 
 int /*<<< orphan*/  time_maxerror ; 
 int time_status ; 
 scalar_t__ time_tai ; 

__attribute__((used)) static inline void process_adjtimex_modes(struct timex *txc, struct timespec *ts)
{
	if (txc->modes & ADJ_STATUS)
		process_adj_status(txc, ts);

	if (txc->modes & ADJ_NANO)
		time_status |= STA_NANO;

	if (txc->modes & ADJ_MICRO)
		time_status &= ~STA_NANO;

	if (txc->modes & ADJ_FREQUENCY) {
		time_freq = txc->freq * PPM_SCALE;
		time_freq = min(time_freq, MAXFREQ_SCALED);
		time_freq = max(time_freq, -MAXFREQ_SCALED);
	}

	if (txc->modes & ADJ_MAXERROR)
		time_maxerror = txc->maxerror;

	if (txc->modes & ADJ_ESTERROR)
		time_esterror = txc->esterror;

	if (txc->modes & ADJ_TIMECONST) {
		time_constant = txc->constant;
		if (!(time_status & STA_NANO))
			time_constant += 4;
		time_constant = min(time_constant, (long)MAXTC);
		time_constant = max(time_constant, 0l);
	}

	if (txc->modes & ADJ_TAI && txc->constant > 0)
		time_tai = txc->constant;

	if (txc->modes & ADJ_OFFSET)
		ntp_update_offset(txc->offset);

	if (txc->modes & ADJ_TICK)
		tick_usec = txc->tick;

	if (txc->modes & (ADJ_TICK|ADJ_FREQUENCY|ADJ_OFFSET))
		ntp_update_frequency();
}