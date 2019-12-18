#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int cpp_num_part ;
struct TYPE_3__ {int low; int high; int unsignedp; int overflow; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 int HIGH_PART (int) ; 
 int LOW_PART (int) ; 
 int PART_PRECISION ; 

__attribute__((used)) static cpp_num
num_part_mul (cpp_num_part lhs, cpp_num_part rhs)
{
  cpp_num result;
  cpp_num_part middle[2], temp;

  result.low = LOW_PART (lhs) * LOW_PART (rhs);
  result.high = HIGH_PART (lhs) * HIGH_PART (rhs);

  middle[0] = LOW_PART (lhs) * HIGH_PART (rhs);
  middle[1] = HIGH_PART (lhs) * LOW_PART (rhs);

  temp = result.low;
  result.low += LOW_PART (middle[0]) << (PART_PRECISION / 2);
  if (result.low < temp)
    result.high++;

  temp = result.low;
  result.low += LOW_PART (middle[1]) << (PART_PRECISION / 2);
  if (result.low < temp)
    result.high++;

  result.high += HIGH_PART (middle[0]);
  result.high += HIGH_PART (middle[1]);
  result.unsignedp = true;
  result.overflow = false;

  return result;
}