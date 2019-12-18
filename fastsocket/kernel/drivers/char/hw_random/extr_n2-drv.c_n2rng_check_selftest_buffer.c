#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct n2rng {TYPE_1__* op; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int SELFTEST_LOOPS_MAX ; 
 int SELFTEST_MATCH_GOAL ; 
 int /*<<< orphan*/  SELFTEST_POLY ; 
 int /*<<< orphan*/  SELFTEST_VAL ; 
 int /*<<< orphan*/  advance_polynomial (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  n2rng_dump_test_buffer (struct n2rng*) ; 
 scalar_t__ n2rng_test_buffer_find (struct n2rng*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int n2rng_check_selftest_buffer(struct n2rng *np, unsigned long unit)
{
	u64 val = SELFTEST_VAL;
	int err, matches, limit;

	matches = 0;
	for (limit = 0; limit < SELFTEST_LOOPS_MAX; limit++) {
		matches += n2rng_test_buffer_find(np, val);
		if (matches >= SELFTEST_MATCH_GOAL)
			break;
		val = advance_polynomial(SELFTEST_POLY, val, 1);
	}

	err = 0;
	if (limit >= SELFTEST_LOOPS_MAX) {
		err = -ENODEV;
		dev_err(&np->op->dev, "Selftest failed on unit %lu\n", unit);
		n2rng_dump_test_buffer(np);
	} else
		dev_info(&np->op->dev, "Selftest passed on unit %lu\n", unit);

	return err;
}