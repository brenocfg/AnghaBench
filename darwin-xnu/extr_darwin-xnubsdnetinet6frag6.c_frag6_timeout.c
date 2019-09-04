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
struct ip6q {TYPE_2__* ip6q_prev; struct ip6q* ip6q_next; int /*<<< orphan*/  ip6q_ttl; } ;
struct fq6_head {int dummy; } ;
struct TYPE_4__ {scalar_t__ ip6q_ttl; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip6s_fragoverflow; int /*<<< orphan*/  ip6s_fragtimeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUFQ_DRAIN (struct fq6_head*) ; 
 int /*<<< orphan*/  MBUFQ_EMPTY (struct fq6_head*) ; 
 int /*<<< orphan*/  MBUFQ_INIT (struct fq6_head*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag6_freef (TYPE_2__*,struct fq6_head*,struct fq6_head*) ; 
 int /*<<< orphan*/  frag6_icmp6_timeex_error (struct fq6_head*) ; 
 unsigned int frag6_nfragpackets ; 
 int /*<<< orphan*/  frag6_sched_timeout () ; 
 scalar_t__ frag6_timeout_run ; 
 scalar_t__ ip6_maxfragpackets ; 
 struct ip6q ip6q ; 
 int /*<<< orphan*/  ip6qlock ; 
 TYPE_1__ ip6stat ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_update_uptime () ; 

__attribute__((used)) static void
frag6_timeout(void *arg)
{
#pragma unused(arg)
	struct fq6_head dfq6, diq6;
	struct ip6q *q6;

	MBUFQ_INIT(&dfq6);	/* for deferred frees */
	MBUFQ_INIT(&diq6);	/* for deferred ICMP time exceeded errors */

	/*
	 * Update coarse-grained networking timestamp (in sec.); the idea
	 * is to piggy-back on the timeout callout to update the counter
	 * returnable via net_uptime().
	 */
	net_update_uptime();

	lck_mtx_lock(&ip6qlock);
	q6 = ip6q.ip6q_next;
	if (q6)
		while (q6 != &ip6q) {
			--q6->ip6q_ttl;
			q6 = q6->ip6q_next;
			if (q6->ip6q_prev->ip6q_ttl == 0) {
				ip6stat.ip6s_fragtimeout++;
				/* XXX in6_ifstat_inc(ifp, ifs6_reass_fail) */
				frag6_freef(q6->ip6q_prev, &dfq6, &diq6);
			}
		}
	/*
	 * If we are over the maximum number of fragments
	 * (due to the limit being lowered), drain off
	 * enough to get down to the new limit.
	 */
	if (ip6_maxfragpackets >= 0) {
		while (frag6_nfragpackets > (unsigned)ip6_maxfragpackets &&
		    ip6q.ip6q_prev) {
			ip6stat.ip6s_fragoverflow++;
			/* XXX in6_ifstat_inc(ifp, ifs6_reass_fail) */
			frag6_freef(ip6q.ip6q_prev, &dfq6, &diq6);
		}
	}
	/* re-arm the purge timer if there's work to do */
	frag6_timeout_run = 0;
	frag6_sched_timeout();
	lck_mtx_unlock(&ip6qlock);

	/* free fragments that need to be freed */
	if (!MBUFQ_EMPTY(&dfq6))
		MBUFQ_DRAIN(&dfq6);

	frag6_icmp6_timeex_error(&diq6);

	VERIFY(MBUFQ_EMPTY(&dfq6));
	VERIFY(MBUFQ_EMPTY(&diq6));
}