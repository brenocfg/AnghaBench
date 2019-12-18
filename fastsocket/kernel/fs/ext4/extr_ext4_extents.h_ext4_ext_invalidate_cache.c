#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {scalar_t__ ec_len; } ;
struct TYPE_4__ {TYPE_1__ i_cached_extent; } ;

/* Variables and functions */
 TYPE_2__* EXT4_I (struct inode*) ; 

__attribute__((used)) static inline void
ext4_ext_invalidate_cache(struct inode *inode)
{
	EXT4_I(inode)->i_cached_extent.ec_len = 0;
}