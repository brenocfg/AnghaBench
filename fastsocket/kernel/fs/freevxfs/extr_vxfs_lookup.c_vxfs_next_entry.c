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
struct vxfs_direct {int d_reclen; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vxfs_direct *
vxfs_next_entry(struct vxfs_direct *de)
{
	return ((struct vxfs_direct *)((char*)de + de->d_reclen));
}