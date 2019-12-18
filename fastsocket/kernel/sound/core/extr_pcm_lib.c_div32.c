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
 unsigned int UINT_MAX ; 

__attribute__((used)) static inline unsigned int div32(unsigned int a, unsigned int b, 
				 unsigned int *r)
{
	if (b == 0) {
		*r = 0;
		return UINT_MAX;
	}
	*r = a % b;
	return a / b;
}