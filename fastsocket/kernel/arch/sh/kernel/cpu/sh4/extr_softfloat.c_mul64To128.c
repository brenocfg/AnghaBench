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
typedef  int bits64 ;
typedef  int bits32 ;

/* Variables and functions */

void mul64To128(bits64 a, bits64 b, bits64 * z0Ptr, bits64 * z1Ptr)
{
	bits32 aHigh, aLow, bHigh, bLow;
	bits64 z0, zMiddleA, zMiddleB, z1;

	aLow = a;
	aHigh = a >> 32;
	bLow = b;
	bHigh = b >> 32;
	z1 = ((bits64) aLow) * bLow;
	zMiddleA = ((bits64) aLow) * bHigh;
	zMiddleB = ((bits64) aHigh) * bLow;
	z0 = ((bits64) aHigh) * bHigh;
	zMiddleA += zMiddleB;
	z0 += (((bits64) (zMiddleA < zMiddleB)) << 32) + (zMiddleA >> 32);
	zMiddleA <<= 32;
	z1 += zMiddleA;
	z0 += (z1 < zMiddleA);
	*z1Ptr = z1;
	*z0Ptr = z0;

}