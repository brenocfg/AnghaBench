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
typedef  scalar_t__ u_long ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_TIMER_MODEMPLUS ; 
 scalar_t__ PLUSWAIT1 ; 
 scalar_t__ PLUSWAIT2 ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
isdn_tty_check_esc(const u_char * p, u_char plus, int count, int *pluscount,
		   u_long *lastplus)
{
	if (plus > 127)
		return;
	if (count > 3) {
		p += count - 3;
		count = 3;
		*pluscount = 0;
	}
	while (count > 0) {
		if (*(p++) == plus) {
			if ((*pluscount)++) {
				/* Time since last '+' > 0.5 sec. ? */
				if (time_after(jiffies, *lastplus + PLUSWAIT1))
					*pluscount = 1;
			} else {
				/* Time since last non-'+' < 1.5 sec. ? */
				if (time_before(jiffies, *lastplus + PLUSWAIT2))
					*pluscount = 0;
			}
			if ((*pluscount == 3) && (count == 1))
				isdn_timer_ctrl(ISDN_TIMER_MODEMPLUS, 1);
			if (*pluscount > 3)
				*pluscount = 1;
		} else
			*pluscount = 0;
		*lastplus = jiffies;
		count--;
	}
}