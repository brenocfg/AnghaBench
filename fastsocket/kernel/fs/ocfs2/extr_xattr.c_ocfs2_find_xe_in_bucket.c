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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ocfs2_xattr_header {struct ocfs2_xattr_entry* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {size_t xe_name_len; int /*<<< orphan*/  xe_name_hash; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 char* bucket_block (struct ocfs2_xattr_bucket*,int) ; 
 struct ocfs2_xattr_header* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_xattr_bucket_get_name_value (int /*<<< orphan*/ ,struct ocfs2_xattr_header*,int,int*,int*) ; 
 int ocfs2_xattr_get_type (struct ocfs2_xattr_entry*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int ocfs2_find_xe_in_bucket(struct inode *inode,
				   struct ocfs2_xattr_bucket *bucket,
				   int name_index,
				   const char *name,
				   u32 name_hash,
				   u16 *xe_index,
				   int *found)
{
	int i, ret = 0, cmp = 1, block_off, new_offset;
	struct ocfs2_xattr_header *xh = bucket_xh(bucket);
	size_t name_len = strlen(name);
	struct ocfs2_xattr_entry *xe = NULL;
	char *xe_name;

	/*
	 * We don't use binary search in the bucket because there
	 * may be multiple entries with the same name hash.
	 */
	for (i = 0; i < le16_to_cpu(xh->xh_count); i++) {
		xe = &xh->xh_entries[i];

		if (name_hash > le32_to_cpu(xe->xe_name_hash))
			continue;
		else if (name_hash < le32_to_cpu(xe->xe_name_hash))
			break;

		cmp = name_index - ocfs2_xattr_get_type(xe);
		if (!cmp)
			cmp = name_len - xe->xe_name_len;
		if (cmp)
			continue;

		ret = ocfs2_xattr_bucket_get_name_value(inode->i_sb,
							xh,
							i,
							&block_off,
							&new_offset);
		if (ret) {
			mlog_errno(ret);
			break;
		}


		xe_name = bucket_block(bucket, block_off) + new_offset;
		if (!memcmp(name, xe_name, name_len)) {
			*xe_index = i;
			*found = 1;
			ret = 0;
			break;
		}
	}

	return ret;
}