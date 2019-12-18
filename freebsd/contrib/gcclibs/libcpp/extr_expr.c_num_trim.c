#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cpp_num_part ;
struct TYPE_4__ {size_t high; size_t low; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 size_t PART_PRECISION ; 

__attribute__((used)) static cpp_num
num_trim (cpp_num num, size_t precision)
{
  if (precision > PART_PRECISION)
    {
      precision -= PART_PRECISION;
      if (precision < PART_PRECISION)
	num.high &= ((cpp_num_part) 1 << precision) - 1;
    }
  else
    {
      if (precision < PART_PRECISION)
	num.low &= ((cpp_num_part) 1 << precision) - 1;
      num.high = 0;
    }

  return num;
}