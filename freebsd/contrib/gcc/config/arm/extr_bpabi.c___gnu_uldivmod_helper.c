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
 unsigned long long __udivdi3 (unsigned long long,unsigned long long) ; 

unsigned long long
__gnu_uldivmod_helper (unsigned long long a, 
		       unsigned long long b,
		       unsigned long long *remainder)
{
  unsigned long long quotient;

  quotient = __udivdi3 (a, b);
  *remainder = a - b * quotient;
  return quotient;
}