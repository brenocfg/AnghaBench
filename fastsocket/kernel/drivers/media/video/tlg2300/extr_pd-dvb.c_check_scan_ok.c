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
struct pd_dvb_adapter {scalar_t__ prev_freq; int bandwidth; long last_jiffies; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  abs (long) ; 
 long jiffies ; 
 unsigned int jiffies_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_scan_ok(__u32 freq, int bandwidth,
			struct pd_dvb_adapter *adapter)
{
	if (bandwidth < 0)
		return false;

	if (adapter->prev_freq == freq
		&& adapter->bandwidth == bandwidth) {
		long nl = jiffies - adapter->last_jiffies;
		unsigned int msec ;

		msec = jiffies_to_msecs(abs(nl));
		return msec > 15000 ? true : false;
	}
	return true;
}