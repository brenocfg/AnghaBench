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
struct ocfs2_super {int max_slots; struct ocfs2_slot_info* slot_info; } ;
struct ocfs2_slot_info {int si_num_slots; struct inode* si_inode; struct ocfs2_slot* si_slots; int /*<<< orphan*/  si_extended; } ;
struct ocfs2_slot {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 int /*<<< orphan*/  SLOT_MAP_SYSTEM_INODE ; 
 int /*<<< orphan*/  __ocfs2_free_slot_info (struct ocfs2_slot_info*) ; 
 struct ocfs2_slot_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_map_slot_buffers (struct ocfs2_super*,struct ocfs2_slot_info*) ; 
 int /*<<< orphan*/  ocfs2_uses_extended_slot_map (struct ocfs2_super*) ; 

int ocfs2_init_slot_info(struct ocfs2_super *osb)
{
	int status;
	struct inode *inode = NULL;
	struct ocfs2_slot_info *si;

	si = kzalloc(sizeof(struct ocfs2_slot_info) +
		     (sizeof(struct ocfs2_slot) * osb->max_slots),
		     GFP_KERNEL);
	if (!si) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	si->si_extended = ocfs2_uses_extended_slot_map(osb);
	si->si_num_slots = osb->max_slots;
	si->si_slots = (struct ocfs2_slot *)((char *)si +
					     sizeof(struct ocfs2_slot_info));

	inode = ocfs2_get_system_file_inode(osb, SLOT_MAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT);
	if (!inode) {
		status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}

	si->si_inode = inode;
	status = ocfs2_map_slot_buffers(osb, si);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	osb->slot_info = (struct ocfs2_slot_info *)si;
bail:
	if (status < 0 && si)
		__ocfs2_free_slot_info(si);

	return status;
}