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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct bintime {int frac; scalar_t__ sec; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int,int*) ; 

__attribute__((used)) static __inline void
bintime2absolutetime(const struct bintime *_bt, uint64_t *abs)
{
	uint64_t nsec;
	nsec = (uint64_t) _bt->sec * (uint64_t)NSEC_PER_SEC + (((uint64_t)NSEC_PER_SEC * (uint32_t)(_bt->frac >> 32)) >> 32);
	nanoseconds_to_absolutetime(nsec, abs);
}