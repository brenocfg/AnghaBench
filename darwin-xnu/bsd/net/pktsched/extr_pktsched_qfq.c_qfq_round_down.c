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
typedef  unsigned long long u_int64_t ;
typedef  unsigned long long u_int32_t ;

/* Variables and functions */

__attribute__((used)) static inline u_int64_t
qfq_round_down(u_int64_t ts, u_int32_t shift)
{
	return (ts & ~((1ULL << shift) - 1));
}