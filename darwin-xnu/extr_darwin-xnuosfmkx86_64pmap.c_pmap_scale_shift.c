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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int GB ; 
 scalar_t__ MIN (int,int) ; 
 int sane_size ; 

__attribute__((used)) static uint32_t pmap_scale_shift(void) {
	uint32_t scale = 0;

	if (sane_size <= 8*GB) {
		scale = (uint32_t)(sane_size / (2 * GB));
	} else if (sane_size <= 32*GB) {
		scale = 4 + (uint32_t)((sane_size - (8 * GB))/ (4 * GB)); 
	} else {
		scale = 10 + (uint32_t)MIN(4, ((sane_size - (32 * GB))/ (8 * GB))); 
	}
	return scale;
}