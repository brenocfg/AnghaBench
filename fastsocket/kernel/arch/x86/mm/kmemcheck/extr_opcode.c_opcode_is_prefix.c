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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static bool opcode_is_prefix(uint8_t b)
{
	return
		/* Group 1 */
		b == 0xf0 || b == 0xf2 || b == 0xf3
		/* Group 2 */
		|| b == 0x2e || b == 0x36 || b == 0x3e || b == 0x26
		|| b == 0x64 || b == 0x65 || b == 0x2e || b == 0x3e
		/* Group 3 */
		|| b == 0x66
		/* Group 4 */
		|| b == 0x67;
}