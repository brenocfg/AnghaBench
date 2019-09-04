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
struct pool {scalar_t__ pool_count; scalar_t__ pool_limit; char* pool_name; int /*<<< orphan*/  pool_zone; int /*<<< orphan*/  pool_fails; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPFPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PF_DEBUG_NOISY ; 
 int PR_NOWAIT ; 
 int PR_WAITOK ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  pf_lock ; 
 void* zalloc_canblock (int /*<<< orphan*/ ,int) ; 

void *
pool_get(struct pool *pp, int flags)
{
	void *buf;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (pp->pool_count > pp->pool_limit) {
		DPFPRINTF(PF_DEBUG_NOISY,
		    ("pf: pool %s hard limit reached (%d)\n",
		    pp->pool_name != NULL ? pp->pool_name : "unknown",
		    pp->pool_limit));
		pp->pool_fails++;
		return (NULL);
	}

	buf = zalloc_canblock(pp->pool_zone, (flags & (PR_NOWAIT | PR_WAITOK)));
	if (buf != NULL) {
		pp->pool_count++;
		VERIFY(pp->pool_count != 0);
	}
	return (buf);
}