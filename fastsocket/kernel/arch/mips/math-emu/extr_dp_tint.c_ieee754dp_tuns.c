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
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754dp_1e31 () ; 
 scalar_t__ ieee754dp_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee754dp_tint (int /*<<< orphan*/ ) ; 

unsigned int ieee754dp_tuns(ieee754dp x)
{
	ieee754dp hb = ieee754dp_1e31();

	/* what if x < 0 ?? */
	if (ieee754dp_lt(x, hb))
		return (unsigned) ieee754dp_tint(x);

	return (unsigned) ieee754dp_tint(ieee754dp_sub(x, hb)) |
	    ((unsigned) 1 << 31);
}