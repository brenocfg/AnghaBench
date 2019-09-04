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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static inline void
tcp_cumulative_stat(u_int32_t cur, u_int32_t *prev, u_int32_t *dest)
{
	/* handle wrap around */
	int32_t diff = (int32_t) (cur - *prev);
	if (diff > 0)
		*dest = diff;
	else
		*dest = 0;
	*prev = cur;
	return;
}