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
typedef  int /*<<< orphan*/  fixp_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cos_table ; 

__attribute__((used)) static inline fixp_t fixp_cos(unsigned int degrees)
{
	int quadrant = (degrees / 90) & 3;
	unsigned int i = degrees % 90;

	if (quadrant == 1 || quadrant == 3)
		i = 90 - i;

	i >>= 1;

	return (quadrant == 1 || quadrant == 2)? -cos_table[i] : cos_table[i];
}