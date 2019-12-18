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
struct rtmsg {int dummy; } ;
struct rtattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RTA_DATA (struct rtattr*) ; 
 int RTA_MAX ; 
 int RTA_METRICS ; 
 int RTA_MULTIPATH ; 
 int RTA_PAYLOAD (struct rtattr*) ; 
 int RTA_TABLE ; 

__attribute__((used)) static int dn_fib_check_attr(struct rtmsg *r, struct rtattr **rta)
{
	int i;

	for(i = 1; i <= RTA_MAX; i++) {
		struct rtattr *attr = rta[i-1];
		if (attr) {
			if (RTA_PAYLOAD(attr) < 4 && RTA_PAYLOAD(attr) != 2)
				return -EINVAL;
			if (i != RTA_MULTIPATH && i != RTA_METRICS &&
			    i != RTA_TABLE)
				rta[i-1] = (struct rtattr *)RTA_DATA(attr);
		}
	}

	return 0;
}