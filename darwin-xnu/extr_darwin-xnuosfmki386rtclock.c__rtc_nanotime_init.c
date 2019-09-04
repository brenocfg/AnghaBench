#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  shift; int /*<<< orphan*/  scale; } ;
typedef  TYPE_1__ pal_rtc_nanotime_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pal_rtc_nanotime_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rdtsc64 () ; 

__attribute__((used)) static inline void
_rtc_nanotime_init(pal_rtc_nanotime_t *rntp, uint64_t base)
{
	uint64_t	tsc = rdtsc64();

	_pal_rtc_nanotime_store(tsc, base, rntp->scale, rntp->shift, rntp);
}