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
typedef  int /*<<< orphan*/  bitmap_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_info_init (int /*<<< orphan*/ *,size_t) ; 
 size_t bitmap_info_ngroups (int /*<<< orphan*/ *) ; 

size_t
bitmap_size(size_t nbits)
{
	bitmap_info_t binfo;

	bitmap_info_init(&binfo, nbits);
	return (bitmap_info_ngroups(&binfo));
}