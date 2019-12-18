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
typedef  scalar_t__ int16 ;
typedef  int float64 ;
typedef  scalar_t__ flag ;
typedef  int bits64 ;

/* Variables and functions */

float64 packFloat64(flag zSign, int16 zExp, bits64 zSig)
{
	return (((bits64) zSign) << 63) + (((bits64) zExp) << 52) + zSig;
}