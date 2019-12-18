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
typedef  int ULONGEST ;

/* Variables and functions */
 int extract_unsigned_integer (void const*,int) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,int) ; 

__attribute__((used)) static void
alpha_lds (void *out, const void *in)
{
  ULONGEST mem     = extract_unsigned_integer (in, 4);
  ULONGEST frac    = (mem >>  0) & 0x7fffff;
  ULONGEST sign    = (mem >> 31) & 1;
  ULONGEST exp_msb = (mem >> 30) & 1;
  ULONGEST exp_low = (mem >> 23) & 0x7f;
  ULONGEST exp, reg;

  exp = (exp_msb << 10) | exp_low;
  if (exp_msb)
    {
      if (exp_low == 0x7f)
	exp = 0x7ff;
    }
  else
    {
      if (exp_low != 0x00)
	exp |= 0x380;
    }

  reg = (sign << 63) | (exp << 52) | (frac << 29);
  store_unsigned_integer (out, 8, reg);
}