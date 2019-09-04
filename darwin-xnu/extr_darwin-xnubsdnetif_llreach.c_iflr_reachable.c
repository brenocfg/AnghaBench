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
typedef  scalar_t__ u_int64_t ;
struct if_llreach {scalar_t__ lr_lastrcvd; scalar_t__ lr_reachable; } ;

/* Variables and functions */
 scalar_t__ net_uptime () ; 

__attribute__((used)) static __inline int
iflr_reachable(struct if_llreach *lr, int cmp_delta, u_int64_t tval)
{
	u_int64_t now;
	u_int64_t expire;

	now = net_uptime();		/* current approx. uptime */
	/*
	 * No need for lr_lock; atomically read the last rcvd uptime.
	 */
	expire = lr->lr_lastrcvd + lr->lr_reachable;
	/*
	 * If we haven't heard back from the local host for over
	 * lr_reachable seconds, consider that the host is no
	 * longer reachable.
	 */
	if (!cmp_delta)
		return (expire >= now);
	/*
	 * If the caller supplied a reference time, consider the
	 * host is reachable if the record hasn't expired (see above)
	 * and if the reference time is within the past lr_reachable
	 * seconds.
	 */
	return ((expire >= now) && (now - tval) < lr->lr_reachable);
}