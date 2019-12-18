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
typedef  scalar_t__ u64 ;
struct the_nilfs {scalar_t__* ns_sbwtime; struct nilfs_super_block** ns_sbp; } ;
struct nilfs_super_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ NILFS_ALTSB_FREQ ; 
 scalar_t__ get_seconds () ; 

__attribute__((used)) static inline int nilfs_altsb_need_update(struct the_nilfs *nilfs)
{
	u64 t = get_seconds();
	struct nilfs_super_block **sbp = nilfs->ns_sbp;
	return sbp[1] && t > nilfs->ns_sbwtime[1] + NILFS_ALTSB_FREQ;
}