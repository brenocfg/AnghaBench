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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ocfs2_xattr_search {struct ocfs2_xattr_bucket* bucket; TYPE_1__* header; int /*<<< orphan*/ * here; scalar_t__ base; scalar_t__ end; } ;
struct ocfs2_xattr_header {scalar_t__ xh_count; struct ocfs2_xattr_entry* xh_entries; scalar_t__ xh_num_buckets; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_hash; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_4__ {scalar_t__ s_blocksize; } ;
struct TYPE_3__ {int /*<<< orphan*/ * xh_entries; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 scalar_t__ bucket_blkno (struct ocfs2_xattr_bucket*) ; 
 scalar_t__ bucket_block (struct ocfs2_xattr_bucket*,int /*<<< orphan*/ ) ; 
 void* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int le16_to_cpu (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char const*,unsigned long long,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_blocks_per_xattr_bucket (TYPE_2__*) ; 
 int ocfs2_find_xe_in_bucket (struct inode*,struct ocfs2_xattr_bucket*,int,char const*,scalar_t__,int*,int*) ; 
 int ocfs2_read_xattr_bucket (struct ocfs2_xattr_bucket*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_free (struct ocfs2_xattr_bucket*) ; 
 struct ocfs2_xattr_bucket* ocfs2_xattr_bucket_new (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (struct ocfs2_xattr_bucket*) ; 

__attribute__((used)) static int ocfs2_xattr_bucket_find(struct inode *inode,
				   int name_index,
				   const char *name,
				   u32 name_hash,
				   u64 p_blkno,
				   u32 first_hash,
				   u32 num_clusters,
				   struct ocfs2_xattr_search *xs)
{
	int ret, found = 0;
	struct ocfs2_xattr_header *xh = NULL;
	struct ocfs2_xattr_entry *xe = NULL;
	u16 index = 0;
	u16 blk_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	int low_bucket = 0, bucket, high_bucket;
	struct ocfs2_xattr_bucket *search;
	u32 last_hash;
	u64 blkno, lower_blkno = 0;

	search = ocfs2_xattr_bucket_new(inode);
	if (!search) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_read_xattr_bucket(search, p_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	xh = bucket_xh(search);
	high_bucket = le16_to_cpu(xh->xh_num_buckets) - 1;
	while (low_bucket <= high_bucket) {
		ocfs2_xattr_bucket_relse(search);

		bucket = (low_bucket + high_bucket) / 2;
		blkno = p_blkno + bucket * blk_per_bucket;
		ret = ocfs2_read_xattr_bucket(search, blkno);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		xh = bucket_xh(search);
		xe = &xh->xh_entries[0];
		if (name_hash < le32_to_cpu(xe->xe_name_hash)) {
			high_bucket = bucket - 1;
			continue;
		}

		/*
		 * Check whether the hash of the last entry in our
		 * bucket is larger than the search one. for an empty
		 * bucket, the last one is also the first one.
		 */
		if (xh->xh_count)
			xe = &xh->xh_entries[le16_to_cpu(xh->xh_count) - 1];

		last_hash = le32_to_cpu(xe->xe_name_hash);

		/* record lower_blkno which may be the insert place. */
		lower_blkno = blkno;

		if (name_hash > le32_to_cpu(xe->xe_name_hash)) {
			low_bucket = bucket + 1;
			continue;
		}

		/* the searched xattr should reside in this bucket if exists. */
		ret = ocfs2_find_xe_in_bucket(inode, search,
					      name_index, name, name_hash,
					      &index, &found);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
		break;
	}

	/*
	 * Record the bucket we have found.
	 * When the xattr's hash value is in the gap of 2 buckets, we will
	 * always set it to the previous bucket.
	 */
	if (!lower_blkno)
		lower_blkno = p_blkno;

	/* This should be in cache - we just read it during the search */
	ret = ocfs2_read_xattr_bucket(xs->bucket, lower_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	xs->header = bucket_xh(xs->bucket);
	xs->base = bucket_block(xs->bucket, 0);
	xs->end = xs->base + inode->i_sb->s_blocksize;

	if (found) {
		xs->here = &xs->header->xh_entries[index];
		mlog(0, "find xattr %s in bucket %llu, entry = %u\n", name,
		     (unsigned long long)bucket_blkno(xs->bucket), index);
	} else
		ret = -ENODATA;

out:
	ocfs2_xattr_bucket_free(search);
	return ret;
}