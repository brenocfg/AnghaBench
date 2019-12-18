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
struct msdos_sb_info {scalar_t__ max_cluster; TYPE_1__* fatent_ops; } ;
struct fat_entry {scalar_t__ entry; } ;
struct TYPE_2__ {scalar_t__ (* ent_next ) (struct fat_entry*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct fat_entry*) ; 

__attribute__((used)) static inline int fat_ent_next(struct msdos_sb_info *sbi,
			       struct fat_entry *fatent)
{
	if (sbi->fatent_ops->ent_next(fatent)) {
		if (fatent->entry < sbi->max_cluster)
			return 1;
	}
	return 0;
}