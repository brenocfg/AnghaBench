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
struct TYPE_2__ {unsigned int pressure; unsigned int x; unsigned int y; } ;
struct corgi_ts {TYPE_1__ tc; } ;

/* Variables and functions */
 unsigned int ADSCTRL_ADR_SH ; 
 unsigned int ADSCTRL_STS ; 
 unsigned long calc_waittime (struct corgi_ts*) ; 
 int /*<<< orphan*/  corgi_ssp_ads7846_get () ; 
 int /*<<< orphan*/  corgi_ssp_ads7846_lock () ; 
 int /*<<< orphan*/  corgi_ssp_ads7846_put (unsigned int) ; 
 int /*<<< orphan*/  corgi_ssp_ads7846_unlock () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned int sync_receive_data_send_cmd (struct corgi_ts*,int,int,unsigned int,unsigned long) ; 

__attribute__((used)) static int read_xydata(struct corgi_ts *corgi_ts)
{
	unsigned int x, y, z1, z2;
	unsigned long flags, wait_time;

	/* critical section */
	local_irq_save(flags);
	corgi_ssp_ads7846_lock();
	wait_time = calc_waittime(corgi_ts);

	/* Y-axis */
	sync_receive_data_send_cmd(corgi_ts, 0, 1, 1u, wait_time);

	/* Y-axis */
	sync_receive_data_send_cmd(corgi_ts, 1, 1, 1u, wait_time);

	/* X-axis */
	y = sync_receive_data_send_cmd(corgi_ts, 1, 1, 5u, wait_time);

	/* Z1 */
	x = sync_receive_data_send_cmd(corgi_ts, 1, 1, 3u, wait_time);

	/* Z2 */
	z1 = sync_receive_data_send_cmd(corgi_ts, 1, 1, 4u, wait_time);
	z2 = sync_receive_data_send_cmd(corgi_ts, 1, 0, 4u, wait_time);

	/* Power-Down Enable */
	corgi_ssp_ads7846_put((1u << ADSCTRL_ADR_SH) | ADSCTRL_STS);
	corgi_ssp_ads7846_get();

	corgi_ssp_ads7846_unlock();
	local_irq_restore(flags);

	if (x== 0 || y == 0 || z1 == 0 || (x * (z2 - z1) / z1) >= 15000) {
		corgi_ts->tc.pressure = 0;
		return 0;
	}

	corgi_ts->tc.x = x;
	corgi_ts->tc.y = y;
	corgi_ts->tc.pressure = (x * (z2 - z1)) / z1;
	return 1;
}