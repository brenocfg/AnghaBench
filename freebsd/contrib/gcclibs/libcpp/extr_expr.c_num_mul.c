#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_14__ {int unsignedp; int overflow; scalar_t__ high; scalar_t__ low; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 size_t CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_eq (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ num_negate (TYPE_1__,size_t) ; 
 TYPE_1__ num_part_mul (scalar_t__,scalar_t__) ; 
 int num_positive (TYPE_1__,size_t) ; 
 TYPE_1__ num_trim (TYPE_1__,size_t) ; 
 int /*<<< orphan*/  num_zerop (TYPE_1__) ; 
 size_t precision ; 

__attribute__((used)) static cpp_num
num_mul (cpp_reader *pfile, cpp_num lhs, cpp_num rhs)
{
  cpp_num result, temp;
  bool unsignedp = lhs.unsignedp || rhs.unsignedp;
  bool overflow, negate = false;
  size_t precision = CPP_OPTION (pfile, precision);

  /* Prepare for unsigned multiplication.  */
  if (!unsignedp)
    {
      if (!num_positive (lhs, precision))
	negate = !negate, lhs = num_negate (lhs, precision);
      if (!num_positive (rhs, precision))
	negate = !negate, rhs = num_negate (rhs, precision);
    }

  overflow = lhs.high && rhs.high;
  result = num_part_mul (lhs.low, rhs.low);

  temp = num_part_mul (lhs.high, rhs.low);
  result.high += temp.low;
  if (temp.high)
    overflow = true;

  temp = num_part_mul (lhs.low, rhs.high);
  result.high += temp.low;
  if (temp.high)
    overflow = true;

  temp.low = result.low, temp.high = result.high;
  result = num_trim (result, precision);
  if (!num_eq (result, temp))
    overflow = true;

  if (negate)
    result = num_negate (result, precision);

  if (unsignedp)
    result.overflow = false;
  else
    result.overflow = overflow || (num_positive (result, precision) ^ !negate
				   && !num_zerop (result));
  result.unsignedp = unsignedp;

  return result;
}