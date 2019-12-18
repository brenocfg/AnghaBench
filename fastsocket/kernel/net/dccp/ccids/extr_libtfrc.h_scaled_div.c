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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ div64_u64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u64 scaled_div(u64 a, u64 b)
{
	BUG_ON(b == 0);
	return div64_u64(a * 1000000, b);
}