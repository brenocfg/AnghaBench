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
typedef  int const uint64_t ;
struct bintime {int frac; int /*<<< orphan*/  sec; } ;
typedef  int clock_usec_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;

/* Variables and functions */

__attribute__((used)) static __inline void
clock2bintime(const clock_sec_t *secs, const clock_usec_t *microsecs, struct bintime *_bt)
{

	_bt->sec = *secs;
	/* 18446744073709 = int(2^64 / 1000000) */
	_bt->frac = *microsecs * (uint64_t)18446744073709LL;
}