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
struct pool {scalar_t__ pool_count; int /*<<< orphan*/  pool_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

void
pool_put(struct pool *pp, void *v)
{
	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	zfree(pp->pool_zone, v);
	VERIFY(pp->pool_count != 0);
	pp->pool_count--;
}