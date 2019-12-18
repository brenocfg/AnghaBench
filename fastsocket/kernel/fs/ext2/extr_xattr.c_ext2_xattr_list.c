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
struct xattr_handler {size_t (* list ) (struct inode*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct ext2_xattr_entry {int /*<<< orphan*/  e_name_len; int /*<<< orphan*/  e_name; int /*<<< orphan*/  e_name_index; } ;
struct buffer_head {char* b_data; int b_size; int /*<<< orphan*/  b_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  i_file_acl; } ;
struct TYPE_3__ {scalar_t__ h_magic; scalar_t__ h_blocks; int /*<<< orphan*/  h_refcount; } ;

/* Variables and functions */
 int EIO ; 
 int ERANGE ; 
 TYPE_2__* EXT2_I (struct inode*) ; 
 int EXT2_XATTR_MAGIC ; 
 struct ext2_xattr_entry* EXT2_XATTR_NEXT (struct ext2_xattr_entry*) ; 
 struct ext2_xattr_entry* FIRST_ENTRY (struct buffer_head*) ; 
 TYPE_1__* HDR (struct buffer_head*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext2_xattr_entry*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,...) ; 
 int /*<<< orphan*/  ext2_error (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2_xattr_cache_insert (struct buffer_head*) ; 
 struct xattr_handler* ext2_xattr_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub1 (struct inode*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ext2_xattr_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	struct ext2_xattr_entry *entry;
	char *end;
	size_t rest = buffer_size;
	int error;

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (long)buffer_size);

	down_read(&EXT2_I(inode)->xattr_sem);
	error = 0;
	if (!EXT2_I(inode)->i_file_acl)
		goto cleanup;
	ea_idebug(inode, "reading block %d", EXT2_I(inode)->i_file_acl);
	bh = sb_bread(inode->i_sb, EXT2_I(inode)->i_file_acl);
	error = -EIO;
	if (!bh)
		goto cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(HDR(bh)->h_refcount));
	end = bh->b_data + bh->b_size;
	if (HDR(bh)->h_magic != cpu_to_le32(EXT2_XATTR_MAGIC) ||
	    HDR(bh)->h_blocks != cpu_to_le32(1)) {
bad_block:	ext2_error(inode->i_sb, "ext2_xattr_list",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}

	/* check the on-disk data structure */
	entry = FIRST_ENTRY(bh);
	while (!IS_LAST_ENTRY(entry)) {
		struct ext2_xattr_entry *next = EXT2_XATTR_NEXT(entry);

		if ((char *)next >= end)
			goto bad_block;
		entry = next;
	}
	if (ext2_xattr_cache_insert(bh))
		ea_idebug(inode, "cache insert failed");

	/* list the attribute names */
	for (entry = FIRST_ENTRY(bh); !IS_LAST_ENTRY(entry);
	     entry = EXT2_XATTR_NEXT(entry)) {
		struct xattr_handler *handler =
			ext2_xattr_handler(entry->e_name_index);

		if (handler) {
			size_t size = handler->list(inode, buffer, rest,
						    entry->e_name,
						    entry->e_name_len);
			if (buffer) {
				if (size > rest) {
					error = -ERANGE;
					goto cleanup;
				}
				buffer += size;
			}
			rest -= size;
		}
	}
	error = buffer_size - rest;  /* total size */

cleanup:
	brelse(bh);
	up_read(&EXT2_I(inode)->xattr_sem);

	return error;
}