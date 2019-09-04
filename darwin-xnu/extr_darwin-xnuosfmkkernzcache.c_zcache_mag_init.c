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
struct zcc_magazine {int zcc_magazine_capacity; scalar_t__ zcc_magazine_index; } ;

/* Variables and functions */

void zcache_mag_init(struct zcc_magazine *mag, int count)
{
	mag->zcc_magazine_index = 0;
	mag->zcc_magazine_capacity = count;
}