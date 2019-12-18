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
struct TYPE_2__ {void* b_last_allocated_ptr; void* b_last_allocated_key; } ;
struct nilfs_direct {TYPE_1__ d_bmap; } ;
typedef  void* __u64 ;

/* Variables and functions */

__attribute__((used)) static void nilfs_direct_set_target_v(struct nilfs_direct *direct,
				      __u64 key, __u64 ptr)
{
	direct->d_bmap.b_last_allocated_key = key;
	direct->d_bmap.b_last_allocated_ptr = ptr;
}