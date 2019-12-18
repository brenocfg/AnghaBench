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
typedef  scalar_t__ uint ;

/* Variables and functions */

__attribute__((used)) static int valid_ea(uint opcode, uint mask)
{
	if(mask == 0)
		return 1;

	switch(opcode & 0x3f)
	{
		case 0x00: case 0x01: case 0x02: case 0x03:
		case 0x04: case 0x05: case 0x06: case 0x07:
			return (mask & 0x800) != 0;
		case 0x08: case 0x09: case 0x0a: case 0x0b:
		case 0x0c: case 0x0d: case 0x0e: case 0x0f:
			return (mask & 0x400) != 0;
		case 0x10: case 0x11: case 0x12: case 0x13:
		case 0x14: case 0x15: case 0x16: case 0x17:
			return (mask & 0x200) != 0;
		case 0x18: case 0x19: case 0x1a: case 0x1b:
		case 0x1c: case 0x1d: case 0x1e: case 0x1f:
			return (mask & 0x100) != 0;
		case 0x20: case 0x21: case 0x22: case 0x23:
		case 0x24: case 0x25: case 0x26: case 0x27:
			return (mask & 0x080) != 0;
		case 0x28: case 0x29: case 0x2a: case 0x2b:
		case 0x2c: case 0x2d: case 0x2e: case 0x2f:
			return (mask & 0x040) != 0;
		case 0x30: case 0x31: case 0x32: case 0x33:
		case 0x34: case 0x35: case 0x36: case 0x37:
			return (mask & 0x020) != 0;
		case 0x38:
			return (mask & 0x010) != 0;
		case 0x39:
			return (mask & 0x008) != 0;
		case 0x3a:
			return (mask & 0x002) != 0;
		case 0x3b:
			return (mask & 0x001) != 0;
		case 0x3c:
			return (mask & 0x004) != 0;
	}
	return 0;

}