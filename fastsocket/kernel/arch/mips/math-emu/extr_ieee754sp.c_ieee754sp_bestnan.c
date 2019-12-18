#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ieee754sp ;

/* Variables and functions */
 scalar_t__ SPMANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754sp_isnan (int /*<<< orphan*/ ) ; 

ieee754sp ieee754sp_bestnan(ieee754sp x, ieee754sp y)
{
	assert(ieee754sp_isnan(x));
	assert(ieee754sp_isnan(y));

	if (SPMANT(x) > SPMANT(y))
		return x;
	else
		return y;
}