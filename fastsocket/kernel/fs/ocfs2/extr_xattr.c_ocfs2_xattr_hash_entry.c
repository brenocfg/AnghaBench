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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_header {int dummy; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_hash; int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_name_offset; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_name_hash (struct inode*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xattr_hash_entry(struct inode *inode,
				   struct ocfs2_xattr_header *header,
				   struct ocfs2_xattr_entry *entry)
{
	u32 hash = 0;
	char *name = (char *)header + le16_to_cpu(entry->xe_name_offset);

	hash = ocfs2_xattr_name_hash(inode, name, entry->xe_name_len);
	entry->xe_name_hash = cpu_to_le32(hash);

	return;
}