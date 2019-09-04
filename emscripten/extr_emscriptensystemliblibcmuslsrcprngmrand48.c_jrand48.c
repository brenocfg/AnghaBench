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
 int __rand48_step (unsigned short*,scalar_t__) ; 
 scalar_t__ __seed48 ; 

long jrand48(unsigned short s[3])
{
	return __rand48_step(s, __seed48+3) >> 16;
}