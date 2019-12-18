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
struct TYPE_4__ {scalar_t__ high; scalar_t__ low; } ;
typedef  TYPE_1__ double_int ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */

int
double_int_scmp (double_int a, double_int b)
{
  if (a.high < b.high)
    return -1;
  if (a.high > b.high)
    return 1;
  if ((HOST_WIDE_INT) a.low < (HOST_WIDE_INT) b.low)
    return -1;
  if ((HOST_WIDE_INT) a.low > (HOST_WIDE_INT) b.low)
    return 1;

  return 0;
}