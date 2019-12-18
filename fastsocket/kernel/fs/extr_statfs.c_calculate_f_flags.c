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
struct vfsmount {TYPE_1__* mnt_sb; int /*<<< orphan*/  mnt_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int ST_VALID ; 
 int flags_by_mnt (int /*<<< orphan*/ ) ; 
 int flags_by_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calculate_f_flags(struct vfsmount *mnt)
{
	return ST_VALID | flags_by_mnt(mnt->mnt_flags) |
		flags_by_sb(mnt->mnt_sb->s_flags);
}