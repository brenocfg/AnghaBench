#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int usage; } ;
struct TYPE_5__ {int flags; int usage; } ;
struct TYPE_4__ {int flags; int usage; } ;
struct btrfs_balance_control {TYPE_3__ meta; TYPE_2__ sys; TYPE_1__ data; } ;

/* Variables and functions */
 int BTRFS_BALANCE_ARGS_CONVERT ; 
 int BTRFS_BALANCE_ARGS_SOFT ; 
 int BTRFS_BALANCE_ARGS_USAGE ; 

__attribute__((used)) static void update_balance_args(struct btrfs_balance_control *bctl)
{
	/*
	 * Turn on soft mode for chunk types that were being converted.
	 */
	if (bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT)
		bctl->data.flags |= BTRFS_BALANCE_ARGS_SOFT;
	if (bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT)
		bctl->sys.flags |= BTRFS_BALANCE_ARGS_SOFT;
	if (bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT)
		bctl->meta.flags |= BTRFS_BALANCE_ARGS_SOFT;

	/*
	 * Turn on usage filter if is not already used.  The idea is
	 * that chunks that we have already balanced should be
	 * reasonably full.  Don't do it for chunks that are being
	 * converted - that will keep us from relocating unconverted
	 * (albeit full) chunks.
	 */
	if (!(bctl->data.flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    !(bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT)) {
		bctl->data.flags |= BTRFS_BALANCE_ARGS_USAGE;
		bctl->data.usage = 90;
	}
	if (!(bctl->sys.flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    !(bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT)) {
		bctl->sys.flags |= BTRFS_BALANCE_ARGS_USAGE;
		bctl->sys.usage = 90;
	}
	if (!(bctl->meta.flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    !(bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT)) {
		bctl->meta.flags |= BTRFS_BALANCE_ARGS_USAGE;
		bctl->meta.usage = 90;
	}
}