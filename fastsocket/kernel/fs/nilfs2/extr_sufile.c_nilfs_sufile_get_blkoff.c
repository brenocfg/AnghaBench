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
struct inode {int dummy; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {scalar_t__ mi_first_entry_offset; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_sufile_segment_usages_per_block (struct inode const*) ; 

__attribute__((used)) static unsigned long
nilfs_sufile_get_blkoff(const struct inode *sufile, __u64 segnum)
{
	__u64 t = segnum + NILFS_MDT(sufile)->mi_first_entry_offset;
	do_div(t, nilfs_sufile_segment_usages_per_block(sufile));
	return (unsigned long)t;
}