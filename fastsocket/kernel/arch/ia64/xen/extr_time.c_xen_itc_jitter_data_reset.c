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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ itc_lastcycle; } ;

/* Variables and functions */
 scalar_t__ cmpxchg (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ itc_jitter_data ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void xen_itc_jitter_data_reset(void)
{
	u64 lcycle, ret;

	do {
		lcycle = itc_jitter_data.itc_lastcycle;
		ret = cmpxchg(&itc_jitter_data.itc_lastcycle, lcycle, 0);
	} while (unlikely(ret != lcycle));
}