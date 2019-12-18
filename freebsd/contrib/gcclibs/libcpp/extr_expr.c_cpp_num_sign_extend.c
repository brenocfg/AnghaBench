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
struct TYPE_4__ {size_t high; size_t low; int /*<<< orphan*/  unsignedp; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 size_t PART_PRECISION ; 

cpp_num
cpp_num_sign_extend (cpp_num num, size_t precision)
{
  if (!num.unsignedp)
    {
      if (precision > PART_PRECISION)
	{
	  precision -= PART_PRECISION;
	  if (precision < PART_PRECISION
	      && (num.high & (cpp_num_part) 1 << (precision - 1)))
	    num.high |= ~(~(cpp_num_part) 0 >> (PART_PRECISION - precision));
	}
      else if (num.low & (cpp_num_part) 1 << (precision - 1))
	{
	  if (precision < PART_PRECISION)
	    num.low |= ~(~(cpp_num_part) 0 >> (PART_PRECISION - precision));
	  num.high = ~(cpp_num_part) 0;
	}
    }

  return num;
}