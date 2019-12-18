#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_3__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct pps_event_time {TYPE_1__ ts_real; } ;
struct efx_ptp_data {scalar_t__ base_sync_ns; scalar_t__ last_sync_ns; int base_sync_valid; struct pps_event_time host_time_pps; TYPE_2__* timeset; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_ptp_data* ptp_data; } ;
struct TYPE_4__ {scalar_t__ window; scalar_t__ waitns; int host_start; scalar_t__ nanoseconds; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EAGAIN ; 
 unsigned int MAX_SYNCHRONISATION_NS ; 
 size_t MC_CMD_PTP_OUT_SYNCHRONIZE_TIMESET_LEN ; 
 int MC_NANOSECOND_BITS ; 
 int MC_NANOSECOND_MASK ; 
 int MC_SECOND_MASK ; 
 unsigned int MIN_SYNCHRONISATION_NS ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_ptp_read_timeset (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pps_sub_ts (struct pps_event_time*,struct timespec) ; 

__attribute__((used)) static int efx_ptp_process_times(struct efx_nic *efx, u8 *synch_buf,
				 size_t response_length,
				 const struct pps_event_time *last_time)
{
	unsigned number_readings = (response_length /
			       MC_CMD_PTP_OUT_SYNCHRONIZE_TIMESET_LEN);
	unsigned i;
	unsigned total;
	unsigned ngood = 0;
	unsigned last_good = 0;
	struct efx_ptp_data *ptp = efx->ptp_data;
	u32 last_sec;
	u32 start_sec;
	struct timespec delta;

	if (number_readings == 0)
		return -EAGAIN;

	/* Read the set of results and increment stats for any results that
	 * appera to be erroneous.
	 */
	for (i = 0; i < number_readings; i++) {
		efx_ptp_read_timeset(synch_buf, &ptp->timeset[i]);
		synch_buf += MC_CMD_PTP_OUT_SYNCHRONIZE_TIMESET_LEN;
	}

	/* Find the last good host-MC synchronization result. The MC times
	 * when it finishes reading the host time so the corrected window time
	 * should be fairly constant for a given platform.
	 */
	total = 0;
	for (i = 0; i < number_readings; i++)
		if (ptp->timeset[i].window > ptp->timeset[i].waitns) {
			unsigned win;

			win = ptp->timeset[i].window - ptp->timeset[i].waitns;
			if (win >= MIN_SYNCHRONISATION_NS &&
			    win < MAX_SYNCHRONISATION_NS) {
				total += ptp->timeset[i].window;
				ngood++;
				last_good = i;
			}
		}

	if (ngood == 0) {
		netif_warn(efx, drv, efx->net_dev,
			   "PTP no suitable synchronisations %dns\n",
			   ptp->base_sync_ns);
		return -EAGAIN;
	}

	/* Average minimum this synchronisation */
	ptp->last_sync_ns = DIV_ROUND_UP(total, ngood);
	if (!ptp->base_sync_valid || (ptp->last_sync_ns < ptp->base_sync_ns)) {
		ptp->base_sync_valid = true;
		ptp->base_sync_ns = ptp->last_sync_ns;
	}

	/* Calculate delay from actual PPS to last_time */
	delta.tv_nsec =
		ptp->timeset[last_good].nanoseconds +
		last_time->ts_real.tv_nsec -
		(ptp->timeset[last_good].host_start & MC_NANOSECOND_MASK);

	/* It is possible that the seconds rolled over between taking
	 * the start reading and the last value written by the host.  The
	 * timescales are such that a gap of more than one second is never
	 * expected.
	 */
	start_sec = ptp->timeset[last_good].host_start >> MC_NANOSECOND_BITS;
	last_sec = last_time->ts_real.tv_sec & MC_SECOND_MASK;
	if (start_sec != last_sec) {
		if (((start_sec + 1) & MC_SECOND_MASK) != last_sec) {
			netif_warn(efx, hw, efx->net_dev,
				   "PTP bad synchronisation seconds\n");
			return -EAGAIN;
		} else {
			delta.tv_sec = 1;
		}
	} else {
		delta.tv_sec = 0;
	}

	ptp->host_time_pps = *last_time;
	pps_sub_ts(&ptp->host_time_pps, delta);

	return 0;
}