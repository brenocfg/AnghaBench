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
 int CCV_PI ; 

__attribute__((used)) static float _ccv_mod_2pi(float x)
{
	while (x > 2 * CCV_PI)
		x -= 2 * CCV_PI;
	while (x < 0)
		x += 2 * CCV_PI;
	return x;
}