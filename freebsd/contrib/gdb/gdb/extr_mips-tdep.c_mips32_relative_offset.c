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
typedef  long CORE_ADDR ;

/* Variables and functions */
 long itype_immediate (unsigned long) ; 

__attribute__((used)) static CORE_ADDR
mips32_relative_offset (unsigned long inst)
{
  long x;
  x = itype_immediate (inst);
  if (x & 0x8000)		/* sign bit set */
    {
      x |= 0xffff0000;		/* sign extension */
    }
  x = x << 2;
  return x;
}