#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cpp_num_part ;
struct TYPE_7__ {size_t high; size_t low; int overflow; scalar_t__ unsignedp; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 size_t PART_PRECISION ; 
 int num_positive (TYPE_1__,size_t) ; 
 TYPE_1__ num_trim (TYPE_1__,size_t) ; 

__attribute__((used)) static cpp_num
num_rshift (cpp_num num, size_t precision, size_t n)
{
  cpp_num_part sign_mask;
  bool x = num_positive (num, precision);

  if (num.unsignedp || x)
    sign_mask = 0;
  else
    sign_mask = ~(cpp_num_part) 0;

  if (n >= precision)
    num.high = num.low = sign_mask;
  else
    {
      /* Sign-extend.  */
      if (precision < PART_PRECISION)
	num.high = sign_mask, num.low |= sign_mask << precision;
      else if (precision < 2 * PART_PRECISION)
	num.high |= sign_mask << (precision - PART_PRECISION);

      if (n >= PART_PRECISION)
	{
	  n -= PART_PRECISION;
	  num.low = num.high;
	  num.high = sign_mask;
	}

      if (n)
	{
	  num.low = (num.low >> n) | (num.high << (PART_PRECISION - n));
	  num.high = (num.high >> n) | (sign_mask << (PART_PRECISION - n));
	}
    }

  num = num_trim (num, precision);
  num.overflow = false;
  return num;
}