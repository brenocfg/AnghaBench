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
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754dp_1e63 () ; 
 int /*<<< orphan*/  ieee754dp_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_flong (unsigned long long) ; 

ieee754dp ieee754dp_fulong(u64 u)
{
	if ((s64) u < 0)
		return ieee754dp_add(ieee754dp_1e63(),
				     ieee754dp_flong(u & ~(1ULL << 63)));
	return ieee754dp_flong(u);
}