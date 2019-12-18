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
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  ieee754dp_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee754dp_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_modf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee754dp_one (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_zero (int /*<<< orphan*/ ) ; 

ieee754dp ieee754dp_ceil(ieee754dp x)
{
	ieee754dp i;

	if (ieee754dp_gt(ieee754dp_modf(x, &i), ieee754dp_zero(0)))
		return ieee754dp_add(i, ieee754dp_one(0));
	else
		return i;
}