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

/* Variables and functions */

__attribute__((used)) static inline int reassemble_17(int as17)
{
	return (((as17 & 0x10000) >> 16) |
		((as17 & 0x0f800) << 5) |
		((as17 & 0x00400) >> 8) |
		((as17 & 0x003ff) << 3));
}