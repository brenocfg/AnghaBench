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

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 unsigned long HZ ; 
 scalar_t__ MAX_JIFFY_OFFSET ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long calc_expire_secs(unsigned long now,
				      unsigned long time,
				      unsigned long expire)
{
	expire = time + expire;

	if (time_after(now, expire))
		return 0; /* expired */
	if (expire < now) {
		/* jiffies wrapped */
		expire -= MAX_JIFFY_OFFSET;
		now -= MAX_JIFFY_OFFSET;
	}
	B43_WARN_ON(expire < now);

	return (expire - now) / HZ;
}