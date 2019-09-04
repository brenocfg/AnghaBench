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
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static inline int
qfq_gt(u_int64_t a, u_int64_t b)
{
	return ((int64_t)(a - b) > 0);
}