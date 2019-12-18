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
struct TYPE_2__ {scalar_t__ head; scalar_t__ tail; } ;
struct e100_serial {unsigned long last_tx_active; unsigned long last_tx_active_usec; int char_time_usec; TYPE_1__ xmit; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long GET_JIFFIES_USEC () ; 
 unsigned long HZ ; 
 unsigned int TIOCSER_TEMT ; 
 scalar_t__ copy_to_user (unsigned int*,unsigned int*,int) ; 
 unsigned long jiffies ; 

__attribute__((used)) static int
get_lsr_info(struct e100_serial * info, unsigned int *value)
{
	unsigned int result = TIOCSER_TEMT;
#ifndef CONFIG_SVINTO_SIM
	unsigned long curr_time = jiffies;
	unsigned long curr_time_usec = GET_JIFFIES_USEC();
	unsigned long elapsed_usec =
		(curr_time - info->last_tx_active) * 1000000/HZ +
		curr_time_usec - info->last_tx_active_usec;

	if (info->xmit.head != info->xmit.tail ||
	    elapsed_usec < 2*info->char_time_usec) {
		result = 0;
	}
#endif

	if (copy_to_user(value, &result, sizeof(int)))
		return -EFAULT;
	return 0;
}