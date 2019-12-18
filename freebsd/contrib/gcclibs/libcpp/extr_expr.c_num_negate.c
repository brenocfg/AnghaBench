#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int overflow; int /*<<< orphan*/  unsignedp; int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ cpp_num ;

/* Variables and functions */
 scalar_t__ num_eq (TYPE_1__,TYPE_1__) ; 
 TYPE_1__ num_trim (TYPE_1__,size_t) ; 
 int /*<<< orphan*/  num_zerop (TYPE_1__) ; 

__attribute__((used)) static cpp_num
num_negate (cpp_num num, size_t precision)
{
  cpp_num copy;

  copy = num;
  num.high = ~num.high;
  num.low = ~num.low;
  if (++num.low == 0)
    num.high++;
  num = num_trim (num, precision);
  num.overflow = (!num.unsignedp && num_eq (num, copy) && !num_zerop (num));

  return num;
}