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
struct jfs_sb_info {int dummy; } ;
struct jfs_inode_info {int active_ag; int /*<<< orphan*/  agno; int /*<<< orphan*/  ixpxd; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_sb; } ;
struct iag {int /*<<< orphan*/  agstart; int /*<<< orphan*/ * inoext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTOAG (int /*<<< orphan*/ ,struct jfs_sb_info*) ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2INOSPERIAG ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
diInitInode(struct inode *ip, int iagno, int ino, int extno, struct iag * iagp)
{
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	struct jfs_inode_info *jfs_ip = JFS_IP(ip);

	ip->i_ino = (iagno << L2INOSPERIAG) + ino;
	jfs_ip->ixpxd = iagp->inoext[extno];
	jfs_ip->agno = BLKTOAG(le64_to_cpu(iagp->agstart), sbi);
	jfs_ip->active_ag = -1;
}