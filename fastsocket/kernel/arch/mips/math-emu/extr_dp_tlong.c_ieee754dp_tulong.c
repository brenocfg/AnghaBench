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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754dp_1e63 () ; 
 scalar_t__ ieee754dp_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee754dp_tlong (int /*<<< orphan*/ ) ; 

u64 ieee754dp_tulong(ieee754dp x)
{
	ieee754dp hb = ieee754dp_1e63();

	/* what if x < 0 ?? */
	if (ieee754dp_lt(x, hb))
		return (u64) ieee754dp_tlong(x);

	return (u64) ieee754dp_tlong(ieee754dp_sub(x, hb)) |
	    (1ULL << 63);
}