#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__** bh; } ;
struct ufs_sb_private_info {unsigned int s_fshift; unsigned int s_fmask; TYPE_2__ s_ubh; } ;
struct TYPE_3__ {void* b_data; } ;

/* Variables and functions */

__attribute__((used)) static inline void *get_usb_offset(struct ufs_sb_private_info *uspi,
				   unsigned int offset)
{
	unsigned int index;
	
	index = offset >> uspi->s_fshift;
	offset &= ~uspi->s_fmask;
	return uspi->s_ubh.bh[index]->b_data + offset;
}