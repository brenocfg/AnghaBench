#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gfs2_inode {TYPE_1__* i_rgd; } ;
struct TYPE_2__ {unsigned int rd_length; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int gfs2_rg_blocks(const struct gfs2_inode *ip,
					  unsigned requested)
{
	if (requested < ip->i_rgd->rd_length)
		return requested + 1;
	return ip->i_rgd->rd_length;
}