#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  ntfs_inode ;
struct TYPE_11__ {TYPE_5__* attr; } ;
typedef  TYPE_3__ ntfs_attr_search_ctx ;
struct TYPE_9__ {int /*<<< orphan*/  value_length; int /*<<< orphan*/  value_offset; } ;
struct TYPE_10__ {TYPE_1__ resident; } ;
struct TYPE_13__ {int non_resident; int /*<<< orphan*/  length; TYPE_2__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent_directory; } ;
typedef  int /*<<< orphan*/  MFT_RECORD ;
typedef  TYPE_4__ FILE_NAME_ATTR ;
typedef  TYPE_5__ ATTR_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FILE_NAME ; 
 int /*<<< orphan*/  CASE_SENSITIVE ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 unsigned long MREF_LE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NTFS_I (struct inode*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_mft_record (int /*<<< orphan*/ *) ; 
 TYPE_3__* ntfs_attr_get_search_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntfs_attr_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ntfs_attr_put_search_ctx (TYPE_3__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_mft_record (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *ntfs_get_parent(struct dentry *child_dent)
{
	struct inode *vi = child_dent->d_inode;
	ntfs_inode *ni = NTFS_I(vi);
	MFT_RECORD *mrec;
	ntfs_attr_search_ctx *ctx;
	ATTR_RECORD *attr;
	FILE_NAME_ATTR *fn;
	unsigned long parent_ino;
	int err;

	ntfs_debug("Entering for inode 0x%lx.", vi->i_ino);
	/* Get the mft record of the inode belonging to the child dentry. */
	mrec = map_mft_record(ni);
	if (IS_ERR(mrec))
		return (struct dentry *)mrec;
	/* Find the first file name attribute in the mft record. */
	ctx = ntfs_attr_get_search_ctx(ni, mrec);
	if (unlikely(!ctx)) {
		unmap_mft_record(ni);
		return ERR_PTR(-ENOMEM);
	}
try_next:
	err = ntfs_attr_lookup(AT_FILE_NAME, NULL, 0, CASE_SENSITIVE, 0, NULL,
			0, ctx);
	if (unlikely(err)) {
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		if (err == -ENOENT)
			ntfs_error(vi->i_sb, "Inode 0x%lx does not have a "
					"file name attribute.  Run chkdsk.",
					vi->i_ino);
		return ERR_PTR(err);
	}
	attr = ctx->attr;
	if (unlikely(attr->non_resident))
		goto try_next;
	fn = (FILE_NAME_ATTR *)((u8 *)attr +
			le16_to_cpu(attr->data.resident.value_offset));
	if (unlikely((u8 *)fn + le32_to_cpu(attr->data.resident.value_length) >
			(u8*)attr + le32_to_cpu(attr->length)))
		goto try_next;
	/* Get the inode number of the parent directory. */
	parent_ino = MREF_LE(fn->parent_directory);
	/* Release the search context and the mft record of the child. */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(ni);

	return d_obtain_alias(ntfs_iget(vi->i_sb, parent_ino));
}