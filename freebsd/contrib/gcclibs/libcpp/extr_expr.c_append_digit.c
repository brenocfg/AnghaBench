#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int cpp_num_part ;
struct TYPE_8__ {unsigned int high; unsigned int low; int overflow; int /*<<< orphan*/  unsignedp; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 unsigned int PART_PRECISION ; 
 int /*<<< orphan*/  num_eq (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ num_trim (TYPE_1__,size_t) ; 

__attribute__((used)) static cpp_num
append_digit (cpp_num num, int digit, int base, size_t precision)
{
  cpp_num result;
  unsigned int shift;
  bool overflow;
  cpp_num_part add_high, add_low;

  /* Multiply by 2, 8 or 16.  Catching this overflow here means we don't
     need to worry about add_high overflowing.  */
  switch (base)
    {
    case 2:
      shift = 1;
      break;

    case 16:
      shift = 4;
      break;

    default:
      shift = 3;
    }
  overflow = !!(num.high >> (PART_PRECISION - shift));
  result.high = num.high << shift;
  result.low = num.low << shift;
  result.high |= num.low >> (PART_PRECISION - shift);
  result.unsignedp = num.unsignedp;

  if (base == 10)
    {
      add_low = num.low << 1;
      add_high = (num.high << 1) + (num.low >> (PART_PRECISION - 1));
    }
  else
    add_high = add_low = 0;

  if (add_low + digit < add_low)
    add_high++;
  add_low += digit;

  if (result.low + add_low < result.low)
    add_high++;
  if (result.high + add_high < result.high)
    overflow = true;

  result.low += add_low;
  result.high += add_high;
  result.overflow = overflow;

  /* The above code catches overflow of a cpp_num type.  This catches
     overflow of the (possibly shorter) target precision.  */
  num.low = result.low;
  num.high = result.high;
  result = num_trim (result, precision);
  if (!num_eq (result, num))
    result.overflow = true;

  return result;
}