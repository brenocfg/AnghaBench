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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline int _ccv_nnc_cmd_ph(const uint32_t cmd)
{
	switch ((cmd >> 16) % 5)
	{
		case 0:
			return ((((cmd >> 17) % 18) + 14) << 1) | (cmd & 1);
		case 1:
			return ((((cmd >> 8) % 33) + 2) << 1) | (cmd & 1);
		case 2:
			return ((((cmd >> 1) % 21) + 12) << 1) | (cmd & 1);
		case 3:
			return ((((cmd >> 14) % 13) + 1) << 1) | (cmd & 1);
		case 4:
		default:
			return ((((cmd >> 1) % 22) + 0) << 1) | (cmd & 1);
	}
}