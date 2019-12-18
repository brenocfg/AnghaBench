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
struct nilfs_sc_info {int dummy; } ;
struct nilfs_sb_info {struct nilfs_sc_info* s_sc_info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct nilfs_sc_info *NILFS_SC(struct nilfs_sb_info *sbi)
{
	return sbi->s_sc_info;
}