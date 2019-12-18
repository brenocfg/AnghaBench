#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ double_int ;

/* Variables and functions */
 int /*<<< orphan*/  add_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

double_int
double_int_add (double_int a, double_int b)
{
  double_int ret;
  add_double (a.low, a.high, b.low, b.high, &ret.low, &ret.high);
  return ret;
}