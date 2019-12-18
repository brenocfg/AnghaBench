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
typedef  int u32 ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int __iwl_read_prph (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  __iwl_write_prph (struct iwl_trans*,int,int) ; 
 scalar_t__ iwl_trans_grab_nic_access (struct iwl_trans*,int,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (struct iwl_trans*,unsigned long*) ; 

void iwl_set_bits_prph(struct iwl_trans *trans, u32 ofs, u32 mask)
{
	unsigned long flags;

	if (iwl_trans_grab_nic_access(trans, false, &flags)) {
		__iwl_write_prph(trans, ofs,
				 __iwl_read_prph(trans, ofs) | mask);
		iwl_trans_release_nic_access(trans, &flags);
	}
}