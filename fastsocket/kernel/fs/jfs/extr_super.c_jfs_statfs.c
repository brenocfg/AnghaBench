#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_5__ {void** val; } ;
struct kstatfs {int f_bfree; int f_bavail; int /*<<< orphan*/  f_namelen; TYPE_2__ f_fsid; void* f_ffree; void* f_files; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct jfs_sb_info {scalar_t__ uuid; TYPE_1__* bmap; int /*<<< orphan*/  bsize; int /*<<< orphan*/  ipimap; } ;
struct inomap {int im_l2nbperiext; int /*<<< orphan*/  im_numfree; int /*<<< orphan*/  im_numinos; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  void* s64 ;
struct TYPE_6__ {struct inomap* i_imap; } ;
struct TYPE_4__ {int db_nfree; int /*<<< orphan*/  db_mapsize; } ;

/* Variables and functions */
 TYPE_3__* JFS_IP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFS_NAME_MAX ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFS_SUPER_MAGIC ; 
 int L2INOSPEREXT ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ crc32_le (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  jfs_info (char*) ; 
 void* min (void*,void*) ; 

__attribute__((used)) static int jfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct jfs_sb_info *sbi = JFS_SBI(dentry->d_sb);
	s64 maxinodes;
	struct inomap *imap = JFS_IP(sbi->ipimap)->i_imap;

	jfs_info("In jfs_statfs");
	buf->f_type = JFS_SUPER_MAGIC;
	buf->f_bsize = sbi->bsize;
	buf->f_blocks = sbi->bmap->db_mapsize;
	buf->f_bfree = sbi->bmap->db_nfree;
	buf->f_bavail = sbi->bmap->db_nfree;
	/*
	 * If we really return the number of allocated & free inodes, some
	 * applications will fail because they won't see enough free inodes.
	 * We'll try to calculate some guess as to how may inodes we can
	 * really allocate
	 *
	 * buf->f_files = atomic_read(&imap->im_numinos);
	 * buf->f_ffree = atomic_read(&imap->im_numfree);
	 */
	maxinodes = min((s64) atomic_read(&imap->im_numinos) +
			((sbi->bmap->db_nfree >> imap->im_l2nbperiext)
			 << L2INOSPEREXT), (s64) 0xffffffffLL);
	buf->f_files = maxinodes;
	buf->f_ffree = maxinodes - (atomic_read(&imap->im_numinos) -
				    atomic_read(&imap->im_numfree));
	buf->f_fsid.val[0] = (u32)crc32_le(0, sbi->uuid, sizeof(sbi->uuid)/2);
	buf->f_fsid.val[1] = (u32)crc32_le(0, sbi->uuid + sizeof(sbi->uuid)/2,
					sizeof(sbi->uuid)/2);

	buf->f_namelen = JFS_NAME_MAX;
	return 0;
}