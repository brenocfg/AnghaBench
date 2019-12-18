#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_8__ {int* val; } ;
struct kstatfs {int f_bsize; int f_blocks; long long f_bavail; long long f_bfree; long long f_files; int /*<<< orphan*/  f_namelen; TYPE_1__ f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
typedef  long long s64 ;
typedef  int pgoff_t ;
struct TYPE_9__ {int nr_clusters; int cluster_size_bits; long long mft_record_size_bits; int serial_no; int /*<<< orphan*/  mftbmp_lock; int /*<<< orphan*/  mft_ino; } ;
typedef  TYPE_2__ ntfs_volume ;
struct TYPE_10__ {int initialized_size; int /*<<< orphan*/  size_lock; } ;
typedef  TYPE_3__ ntfs_inode ;

/* Variables and functions */
 TYPE_3__* NTFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTFS_MAX_NAME_LEN ; 
 TYPE_2__* NTFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  NTFS_SB_MAGIC ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  __get_nr_free_mft_records (TYPE_2__*,long long,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int get_nr_free_clusters (TYPE_2__*) ; 
 long long i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ntfs_statfs(struct dentry *dentry, struct kstatfs *sfs)
{
	struct super_block *sb = dentry->d_sb;
	s64 size;
	ntfs_volume *vol = NTFS_SB(sb);
	ntfs_inode *mft_ni = NTFS_I(vol->mft_ino);
	pgoff_t max_index;
	unsigned long flags;

	ntfs_debug("Entering.");
	/* Type of filesystem. */
	sfs->f_type   = NTFS_SB_MAGIC;
	/* Optimal transfer block size. */
	sfs->f_bsize  = PAGE_CACHE_SIZE;
	/*
	 * Total data blocks in filesystem in units of f_bsize and since
	 * inodes are also stored in data blocs ($MFT is a file) this is just
	 * the total clusters.
	 */
	sfs->f_blocks = vol->nr_clusters << vol->cluster_size_bits >>
				PAGE_CACHE_SHIFT;
	/* Free data blocks in filesystem in units of f_bsize. */
	size	      = get_nr_free_clusters(vol) << vol->cluster_size_bits >>
				PAGE_CACHE_SHIFT;
	if (size < 0LL)
		size = 0LL;
	/* Free blocks avail to non-superuser, same as above on NTFS. */
	sfs->f_bavail = sfs->f_bfree = size;
	/* Serialize accesses to the inode bitmap. */
	down_read(&vol->mftbmp_lock);
	read_lock_irqsave(&mft_ni->size_lock, flags);
	size = i_size_read(vol->mft_ino) >> vol->mft_record_size_bits;
	/*
	 * Convert the maximum number of set bits into bytes rounded up, then
	 * convert into multiples of PAGE_CACHE_SIZE, rounding up so that if we
	 * have one full and one partial page max_index = 2.
	 */
	max_index = ((((mft_ni->initialized_size >> vol->mft_record_size_bits)
			+ 7) >> 3) + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT;
	read_unlock_irqrestore(&mft_ni->size_lock, flags);
	/* Number of inodes in filesystem (at this point in time). */
	sfs->f_files = size;
	/* Free inodes in fs (based on current total count). */
	sfs->f_ffree = __get_nr_free_mft_records(vol, size, max_index);
	up_read(&vol->mftbmp_lock);
	/*
	 * File system id. This is extremely *nix flavour dependent and even
	 * within Linux itself all fs do their own thing. I interpret this to
	 * mean a unique id associated with the mounted fs and not the id
	 * associated with the filesystem driver, the latter is already given
	 * by the filesystem type in sfs->f_type. Thus we use the 64-bit
	 * volume serial number splitting it into two 32-bit parts. We enter
	 * the least significant 32-bits in f_fsid[0] and the most significant
	 * 32-bits in f_fsid[1].
	 */
	sfs->f_fsid.val[0] = vol->serial_no & 0xffffffff;
	sfs->f_fsid.val[1] = (vol->serial_no >> 32) & 0xffffffff;
	/* Maximum length of filenames. */
	sfs->f_namelen	   = NTFS_MAX_NAME_LEN;
	return 0;
}