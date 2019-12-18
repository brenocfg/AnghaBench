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
 int /*<<< orphan*/  ieee754dp_modf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ieee754dp ieee754dp_trunc(ieee754dp x)
{
	ieee754dp i;

	(void) ieee754dp_modf(x, &i);
	return i;
}