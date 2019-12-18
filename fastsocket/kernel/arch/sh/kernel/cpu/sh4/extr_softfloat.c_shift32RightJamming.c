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
typedef  int int16 ;
typedef  int bits32 ;

/* Variables and functions */

void shift32RightJamming(bits32 a, int16 count, bits32 * zPtr)
{
	bits32 z;
	if (count == 0) {
		z = a;
	} else if (count < 32) {
		z = (a >> count) | ((a << ((-count) & 31)) != 0);
	} else {
		z = (a != 0);
	}
	*zPtr = z;
}