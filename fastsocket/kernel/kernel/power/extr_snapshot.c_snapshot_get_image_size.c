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
 unsigned long nr_copy_pages ; 
 unsigned long nr_meta_pages ; 

unsigned long snapshot_get_image_size(void)
{
	return nr_copy_pages + nr_meta_pages + 1;
}