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
struct bintime {int sec; } ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  bintime_subx (struct bintime*,int) ; 

__attribute__((used)) static __inline void
bintime_subns(struct bintime *bt, uint64_t ns)
{
	bt->sec -= ns/ (uint64_t)NSEC_PER_SEC;
	ns = ns % (uint64_t)NSEC_PER_SEC;
	if (ns) {
		/* 18446744073 = int(2^64 / NSEC_PER_SEC) */
		ns = ns * (uint64_t)18446744073LL;
		bintime_subx(bt, ns);
	}
}