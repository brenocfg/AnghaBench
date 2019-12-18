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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static inline int between(u32 lower, u32 upper, u32 n)
{
	if ((lower < n) && (n < upper))
		return 1;
	if ((upper < lower) && ((n > lower) || (n < upper)))
		return 1;
	return 0;
}