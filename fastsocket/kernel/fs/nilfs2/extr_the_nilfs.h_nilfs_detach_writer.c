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
struct the_nilfs {int /*<<< orphan*/  ns_writer_sem; struct nilfs_sb_info* ns_writer; } ;
struct nilfs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
nilfs_detach_writer(struct the_nilfs *nilfs, struct nilfs_sb_info *sbi)
{
	down_write(&nilfs->ns_writer_sem);
	if (sbi == nilfs->ns_writer)
		nilfs->ns_writer = NULL;
	up_write(&nilfs->ns_writer_sem);
}