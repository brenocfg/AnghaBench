#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bufattr {int /*<<< orphan*/  ba_flags; } ;
struct _throttle_io_info_t {int dummy; } ;
typedef  TYPE_1__* mount_t ;
typedef  TYPE_2__* buf_t ;
struct TYPE_8__ {TYPE_1__* v_mount; } ;
struct TYPE_7__ {struct bufattr b_attr; } ;
struct TYPE_6__ {size_t mnt_devbsdunit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA_IO_TIER_UPGRADE ; 
 int /*<<< orphan*/  BA_STRATEGY_TRACKED_IO ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GET_BUFATTR_IO_TIER (struct bufattr*) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOWPRI_MAX_NUM_DEV ; 
 struct _throttle_io_info_t* _throttle_io_info ; 
 TYPE_4__* buf_vnode (TYPE_2__*) ; 
 int /*<<< orphan*/  throttle_info_end_io_internal (struct _throttle_io_info_t*,int) ; 

void throttle_info_end_io(buf_t bp) {
	mount_t mp;
	struct bufattr *bap;
	struct _throttle_io_info_t *info;
	int io_tier;

	bap = &bp->b_attr;
	if (!ISSET(bap->ba_flags, BA_STRATEGY_TRACKED_IO)) {
		return;
	}
	CLR(bap->ba_flags, BA_STRATEGY_TRACKED_IO);

	mp = buf_vnode(bp)->v_mount;
	if (mp != NULL) {
		info = &_throttle_io_info[mp->mnt_devbsdunit];
	} else {
		info = &_throttle_io_info[LOWPRI_MAX_NUM_DEV - 1];
	}

	io_tier = GET_BUFATTR_IO_TIER(bap);
	if (ISSET(bap->ba_flags, BA_IO_TIER_UPGRADE)) {
		io_tier--;
	}

	throttle_info_end_io_internal(info, io_tier);
}