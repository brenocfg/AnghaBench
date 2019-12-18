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
struct dst_entry {unsigned long rate_tokens; unsigned long rate_last; } ;

/* Variables and functions */
 int XRLIM_BURST_FACTOR ; 
 unsigned long jiffies ; 

int xrlim_allow(struct dst_entry *dst, int timeout)
{
	unsigned long now, token = dst->rate_tokens;
	int rc = 0;

	now = jiffies;
	token += now - dst->rate_last;
	dst->rate_last = now;
	if (token > XRLIM_BURST_FACTOR * timeout)
		token = XRLIM_BURST_FACTOR * timeout;
	if (token >= timeout) {
		token -= timeout;
		rc = 1;
	}
	dst->rate_tokens = token;
	return rc;
}