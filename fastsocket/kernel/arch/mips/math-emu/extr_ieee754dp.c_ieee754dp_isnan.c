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
 scalar_t__ IEEE754_CLASS_SNAN ; 
 scalar_t__ ieee754dp_class (int /*<<< orphan*/ ) ; 

int ieee754dp_isnan(ieee754dp x)
{
	return ieee754dp_class(x) >= IEEE754_CLASS_SNAN;
}