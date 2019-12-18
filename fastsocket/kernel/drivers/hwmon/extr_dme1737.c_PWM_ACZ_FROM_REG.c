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

__attribute__((used)) static inline int PWM_ACZ_FROM_REG(int reg)
{
	static const int acz[] = {1, 2, 4, 0, 0, 6, 7, 0};

	return acz[(reg >> 5) & 0x07];
}