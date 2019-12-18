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
 short munge_sample (short) ; 

__attribute__((used)) static void munge_sample_array(short *array, unsigned int num_elements)
{
	unsigned int i;

	for (i = 0; i < num_elements; i++) {
		array[i] = munge_sample(array[i]);
	}
}