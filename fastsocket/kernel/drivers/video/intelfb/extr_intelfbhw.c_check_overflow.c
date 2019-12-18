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
 int /*<<< orphan*/  WRN_MSG (char*,char const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static __inline__ int check_overflow(u32 value, u32 limit,
				     const char *description)
{
	if (value > limit) {
		WRN_MSG("%s value %d exceeds limit %d\n",
			description, value, limit);
		return 1;
	}
	return 0;
}