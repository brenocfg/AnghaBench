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
struct radeon_fence {scalar_t__ ring; scalar_t__ seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline bool radeon_fence_is_earlier(struct radeon_fence *a,
					   struct radeon_fence *b)
{
	if (!a) {
		return false;
	}

	if (!b) {
		return true;
	}

	BUG_ON(a->ring != b->ring);

	return a->seq < b->seq;
}