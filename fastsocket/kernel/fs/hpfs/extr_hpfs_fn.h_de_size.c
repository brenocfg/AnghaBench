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
typedef  scalar_t__ secno ;

/* Variables and functions */

__attribute__((used)) static inline unsigned de_size(int namelen, secno down_ptr)
{
	return ((0x1f + namelen + 3) & ~3) + (down_ptr ? 4 : 0);
}