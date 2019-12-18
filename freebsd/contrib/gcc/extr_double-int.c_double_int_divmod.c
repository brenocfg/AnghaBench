#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ double_int ;

/* Variables and functions */
 int /*<<< orphan*/  div_and_round_double (unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

double_int
double_int_divmod (double_int a, double_int b, bool uns, unsigned code,
		   double_int *mod)
{
  double_int ret;

  div_and_round_double (code, uns, a.low, a.high, b.low, b.high,
			&ret.low, &ret.high, &mod->low, &mod->high);
  return ret;
}