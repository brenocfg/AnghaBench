#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int RegSetSize; int* RegSet; } ;
typedef  TYPE_1__ MCRegisterClass ;

/* Variables and functions */

bool MCRegisterClass_contains(const MCRegisterClass *c, unsigned Reg)
{
	unsigned InByte = Reg % 8;
	unsigned Byte = Reg / 8;

	if (Byte >= c->RegSetSize)
		return false;

	return (c->RegSet[Byte] & (1 << InByte)) != 0;
}