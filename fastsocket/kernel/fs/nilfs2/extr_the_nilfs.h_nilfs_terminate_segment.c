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
struct the_nilfs {scalar_t__ ns_pseg_offset; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */

__attribute__((used)) static inline void
nilfs_terminate_segment(struct the_nilfs *nilfs, sector_t seg_start,
			sector_t seg_end)
{
	/* terminate the current full segment (used in case of I/O-error) */
	nilfs->ns_pseg_offset = seg_end - seg_start + 1;
}