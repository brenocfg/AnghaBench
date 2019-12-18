#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fq6_head {int dummy; } ;
struct TYPE_5__ {struct TYPE_5__* ip6q_next; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip6s_fragdropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUFQ_DRAIN (struct fq6_head*) ; 
 int /*<<< orphan*/  MBUFQ_EMPTY (struct fq6_head*) ; 
 int /*<<< orphan*/  MBUFQ_INIT (struct fq6_head*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag6_freef (TYPE_2__*,struct fq6_head*,struct fq6_head*) ; 
 int /*<<< orphan*/  frag6_icmp6_timeex_error (struct fq6_head*) ; 
 TYPE_2__ ip6q ; 
 int /*<<< orphan*/  ip6qlock ; 
 TYPE_1__ ip6stat ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
frag6_drain(void)
{
	struct fq6_head dfq6, diq6;

	MBUFQ_INIT(&dfq6);	/* for deferred frees */
	MBUFQ_INIT(&diq6);	/* for deferred ICMP time exceeded errors */

	lck_mtx_lock(&ip6qlock);
	while (ip6q.ip6q_next != &ip6q) {
		ip6stat.ip6s_fragdropped++;
		/* XXX in6_ifstat_inc(ifp, ifs6_reass_fail) */
		frag6_freef(ip6q.ip6q_next, &dfq6, &diq6);
	}
	lck_mtx_unlock(&ip6qlock);

	/* free fragments that need to be freed */
	if (!MBUFQ_EMPTY(&dfq6))
		MBUFQ_DRAIN(&dfq6);

	frag6_icmp6_timeex_error(&diq6);

	VERIFY(MBUFQ_EMPTY(&dfq6));
	VERIFY(MBUFQ_EMPTY(&diq6));
}