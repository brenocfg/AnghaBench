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
 scalar_t__ rdseed_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rdseed_retry(uint64_t * seed, size_t nretries)
{
	size_t i;

	for (i = 0; i < nretries; i += 1) {
		if (rdseed_step(seed)) {
			return 1;
		} else {
			asm volatile("pause");
		}
	}

	return 0;
}