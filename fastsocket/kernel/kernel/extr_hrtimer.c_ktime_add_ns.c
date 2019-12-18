#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_8__ {scalar_t__ tv64; } ;
typedef  TYPE_1__ ktime_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 unsigned long do_div (scalar_t__,scalar_t__) ; 
 TYPE_1__ ktime_add (TYPE_1__ const,TYPE_1__) ; 
 TYPE_1__ ktime_set (long,unsigned long) ; 
 scalar_t__ likely (int) ; 

ktime_t ktime_add_ns(const ktime_t kt, u64 nsec)
{
	ktime_t tmp;

	if (likely(nsec < NSEC_PER_SEC)) {
		tmp.tv64 = nsec;
	} else {
		unsigned long rem = do_div(nsec, NSEC_PER_SEC);

		tmp = ktime_set((long)nsec, rem);
	}

	return ktime_add(kt, tmp);
}