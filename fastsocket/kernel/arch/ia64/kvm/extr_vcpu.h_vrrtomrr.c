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
union ia64_rr {unsigned long val; int rid; scalar_t__ ps; int ve; } ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 

__attribute__((used)) static inline unsigned long vrrtomrr(unsigned long val)
{
	union ia64_rr rr;
	rr.val = val;
	rr.rid = (rr.rid << 4) | 0xe;
	if (rr.ps > PAGE_SHIFT)
		rr.ps = PAGE_SHIFT;
	rr.ve = 1;
	return rr.val;
}