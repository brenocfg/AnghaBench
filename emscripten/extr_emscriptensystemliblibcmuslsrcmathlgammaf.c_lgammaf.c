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

/* Variables and functions */
 float __lgammaf_r (float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __signgam ; 

float lgammaf(float x)
{
	return __lgammaf_r(x, &__signgam);
}