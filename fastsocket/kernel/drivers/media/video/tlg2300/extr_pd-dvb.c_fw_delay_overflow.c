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
struct pd_dvb_adapter {long last_jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  abs (long) ; 
 long jiffies ; 
 unsigned int jiffies_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fw_delay_overflow(struct pd_dvb_adapter *adapter)
{
	long nl = jiffies - adapter->last_jiffies;
	unsigned int msec ;

	msec = jiffies_to_msecs(abs(nl));
	return msec > 800 ? true : false;
}