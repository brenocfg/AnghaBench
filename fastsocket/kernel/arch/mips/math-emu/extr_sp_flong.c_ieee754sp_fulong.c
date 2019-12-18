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
typedef  int /*<<< orphan*/  ieee754sp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754sp_1e63 () ; 
 int /*<<< orphan*/  ieee754sp_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754sp_flong (unsigned long long) ; 

ieee754sp ieee754sp_fulong(u64 u)
{
	if ((s64) u < 0)
		return ieee754sp_add(ieee754sp_1e63(),
				     ieee754sp_flong(u & ~(1ULL << 63)));
	return ieee754sp_flong(u);
}