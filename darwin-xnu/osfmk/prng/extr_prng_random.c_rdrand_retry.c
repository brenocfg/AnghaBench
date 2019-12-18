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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ rdrand_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rdrand_retry(uint64_t * rand, size_t nretries)
{
	size_t i;

	for (i = 0; i < nretries; i += 1) {
		if (rdrand_step(rand)) {
			return 1;
		}
	}

	return 0;
}