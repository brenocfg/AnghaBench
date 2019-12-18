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
struct cache_head {int /*<<< orphan*/  flags; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int /*<<< orphan*/  CACHE_VALID ; 
 int EAGAIN ; 
 int ENOENT ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int cache_is_valid(struct cache_detail *detail, struct cache_head *h)
{
	if (!test_bit(CACHE_VALID, &h->flags))
		return -EAGAIN;
	else {
		/* entry is valid */
		if (test_bit(CACHE_NEGATIVE, &h->flags))
			return -ENOENT;
		else {
			/*
			 * In combination with write barrier in
			 * sunrpc_cache_update, ensures that anyone
			 * using the cache entry after this sees the
			 * updated contents:
			 */
			smp_rmb();
			return 0;
		}
	}
}