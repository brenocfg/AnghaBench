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
struct TYPE_3__ {int quot; int rem; } ;
typedef  TYPE_1__ div_t ;

/* Variables and functions */

div_t div(int numerator, int denominator) {
  div_t x;
  x.quot=numerator/denominator;
  x.rem=numerator-x.quot*denominator;
  return x;
}