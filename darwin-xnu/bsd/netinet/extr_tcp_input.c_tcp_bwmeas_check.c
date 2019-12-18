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
typedef  int uint32_t ;
struct tcpcb {scalar_t__ snd_una; int t_flagsext; TYPE_1__* t_bwmeas; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ bw_start; int bw_ts; int bw_sndbw; int bw_sndbw_max; scalar_t__ bw_size; } ;

/* Variables and functions */
 scalar_t__ SEQ_LEQ (scalar_t__,scalar_t__) ; 
 int TF_BWMEAS_INPROGRESS ; 
 int max (int,int) ; 
 int tcp_now ; 

__attribute__((used)) static void
tcp_bwmeas_check(struct tcpcb *tp)
{
	int32_t bw_meas_bytes;
	uint32_t bw, bytes, elapsed_time;

	if (SEQ_LEQ(tp->snd_una, tp->t_bwmeas->bw_start))
		return;

	bw_meas_bytes = tp->snd_una - tp->t_bwmeas->bw_start;
	if ((tp->t_flagsext & TF_BWMEAS_INPROGRESS) &&
	    bw_meas_bytes >= (int32_t)(tp->t_bwmeas->bw_size)) {
		bytes = bw_meas_bytes;
		elapsed_time = tcp_now - tp->t_bwmeas->bw_ts;
		if (elapsed_time > 0) {
			bw = bytes / elapsed_time;
			if ( bw > 0) {
				if (tp->t_bwmeas->bw_sndbw > 0) {
					tp->t_bwmeas->bw_sndbw =
					    (((tp->t_bwmeas->bw_sndbw << 3)
					    - tp->t_bwmeas->bw_sndbw)
					    + bw) >> 3;
				} else {
					tp->t_bwmeas->bw_sndbw = bw;
				}

				/* Store the maximum value */
				if (tp->t_bwmeas->bw_sndbw_max == 0) {
					tp->t_bwmeas->bw_sndbw_max =
					    tp->t_bwmeas->bw_sndbw;
				} else {
					tp->t_bwmeas->bw_sndbw_max =
					    max(tp->t_bwmeas->bw_sndbw,
					    tp->t_bwmeas->bw_sndbw_max);
				}
			}
		}
		tp->t_flagsext &= ~(TF_BWMEAS_INPROGRESS);
	}
}