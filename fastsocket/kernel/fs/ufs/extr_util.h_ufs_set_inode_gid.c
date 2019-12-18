#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {void* ui_sgid; } ;
struct TYPE_11__ {TYPE_4__ oldids; } ;
struct TYPE_7__ {void* ui_gid; } ;
struct TYPE_8__ {void* ui_gid; } ;
struct TYPE_9__ {TYPE_1__ ui_sun; TYPE_2__ ui_44; } ;
struct ufs_inode {TYPE_5__ ui_u1; TYPE_3__ ui_u3; } ;
struct super_block {int dummy; } ;
struct TYPE_12__ {int s_flags; } ;

/* Variables and functions */
 TYPE_6__* UFS_SB (struct super_block*) ; 
#define  UFS_UID_44BSD 129 
#define  UFS_UID_EFT 128 
 int UFS_UID_MASK ; 
 void* cpu_to_fs16 (struct super_block*,int) ; 
 void* cpu_to_fs32 (struct super_block*,int) ; 

__attribute__((used)) static inline void
ufs_set_inode_gid(struct super_block *sb, struct ufs_inode *inode, u32 value)
{
	switch (UFS_SB(sb)->s_flags & UFS_UID_MASK) {
	case UFS_UID_44BSD:
		inode->ui_u3.ui_44.ui_gid = cpu_to_fs32(sb, value);
		inode->ui_u1.oldids.ui_sgid =  cpu_to_fs16(sb, value);
		break;
	case UFS_UID_EFT:
		inode->ui_u3.ui_sun.ui_gid = cpu_to_fs32(sb, value);
		if (value > 0xFFFF)
			value = 0xFFFF;
		/* Fall through */
	default:
		inode->ui_u1.oldids.ui_sgid =  cpu_to_fs16(sb, value);
		break;
	}
}