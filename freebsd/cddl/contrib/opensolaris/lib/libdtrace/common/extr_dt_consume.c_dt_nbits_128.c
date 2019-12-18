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
 scalar_t__ dt_gt_128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_shift_128 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
dt_nbits_128(uint64_t *a)
{
	int nbits = 0;
	uint64_t tmp[2];
	uint64_t zero[2] = { 0, 0 };

	tmp[0] = a[0];
	tmp[1] = a[1];

	dt_shift_128(tmp, -1);
	while (dt_gt_128(tmp, zero)) {
		dt_shift_128(tmp, -1);
		nbits++;
	}

	return (nbits);
}