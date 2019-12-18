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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {unsigned int e_flags; int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
typedef  int /*<<< orphan*/  replace_rec ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EROFS ; 
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_error (struct super_block*,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 struct super_block* ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_metadata_cache_owner (int /*<<< orphan*/ ) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 int ocfs2_search_extent_list (struct ocfs2_extent_list*,int /*<<< orphan*/ ) ; 
 int ocfs2_split_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,int,struct ocfs2_extent_rec*,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_clear_ext_refcount(handle_t *handle,
				    struct ocfs2_extent_tree *et,
				    u32 cpos, u32 p_cluster, u32 len,
				    unsigned int ext_flags,
				    struct ocfs2_alloc_context *meta_ac,
				    struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret, index;
	struct ocfs2_extent_rec replace_rec;
	struct ocfs2_path *path = NULL;
	struct ocfs2_extent_list *el;
	struct super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	u64 ino = ocfs2_metadata_cache_owner(et->et_ci);

	mlog(0, "inode %llu cpos %u, len %u, p_cluster %u, ext_flags %u\n",
	     (unsigned long long)ino, cpos, len, p_cluster, ext_flags);

	memset(&replace_rec, 0, sizeof(replace_rec));
	replace_rec.e_cpos = cpu_to_le32(cpos);
	replace_rec.e_leaf_clusters = cpu_to_le16(len);
	replace_rec.e_blkno = cpu_to_le64(ocfs2_clusters_to_blocks(sb,
								   p_cluster));
	replace_rec.e_flags = ext_flags;
	replace_rec.e_flags &= ~OCFS2_EXT_REFCOUNTED;

	path = ocfs2_new_path_from_et(et);
	if (!path) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_path(et->et_ci, path, cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	el = path_leaf_el(path);

	index = ocfs2_search_extent_list(el, cpos);
	if (index == -1 || index >= le16_to_cpu(el->l_next_free_rec)) {
		ocfs2_error(sb,
			    "Inode %llu has an extent at cpos %u which can no "
			    "longer be found.\n",
			    (unsigned long long)ino, cpos);
		ret = -EROFS;
		goto out;
	}

	ret = ocfs2_split_extent(handle, et, path, index,
				 &replace_rec, meta_ac, dealloc);
	if (ret)
		mlog_errno(ret);

out:
	ocfs2_free_path(path);
	return ret;
}