#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fs_state; } ;
struct TYPE_12__ {int /*<<< orphan*/  fs_state; } ;
struct TYPE_13__ {TYPE_1__ fs_44; TYPE_4__ fs_sun; } ;
struct ufs_super_block_third {TYPE_5__ fs_un2; int /*<<< orphan*/  fs_postblformat; } ;
struct TYPE_15__ {int /*<<< orphan*/  fs_state; } ;
struct TYPE_14__ {TYPE_7__ fs_sunx86; } ;
struct TYPE_10__ {int /*<<< orphan*/  fs_state; } ;
struct TYPE_11__ {TYPE_2__ fs_sun; } ;
struct ufs_super_block_first {TYPE_6__ fs_u1; TYPE_3__ fs_u0; } ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_16__ {int s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_42POSTBLFMT ; 
 TYPE_8__* UFS_SB (struct super_block*) ; 
#define  UFS_ST_44BSD 131 
 int UFS_ST_MASK ; 
#define  UFS_ST_SUN 130 
#define  UFS_ST_SUNOS 129 
#define  UFS_ST_SUNx86 128 
 int /*<<< orphan*/  fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline s32
ufs_get_fs_state(struct super_block *sb, struct ufs_super_block_first *usb1,
		 struct ufs_super_block_third *usb3)
{
	switch (UFS_SB(sb)->s_flags & UFS_ST_MASK) {
	case UFS_ST_SUNOS:
		if (fs32_to_cpu(sb, usb3->fs_postblformat) == UFS_42POSTBLFMT)
			return fs32_to_cpu(sb, usb1->fs_u0.fs_sun.fs_state);
		/* Fall Through to UFS_ST_SUN */
	case UFS_ST_SUN:
		return fs32_to_cpu(sb, usb3->fs_un2.fs_sun.fs_state);
	case UFS_ST_SUNx86:
		return fs32_to_cpu(sb, usb1->fs_u1.fs_sunx86.fs_state);
	case UFS_ST_44BSD:
	default:
		return fs32_to_cpu(sb, usb3->fs_un2.fs_44.fs_state);
	}
}