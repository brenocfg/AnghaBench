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
struct inode {int i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int OMFS_DIR_START ; 
 int /*<<< orphan*/  OMFS_SB (int /*<<< orphan*/ ) ; 
 int clus_to_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omfs_hash (char const*,int,int) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct buffer_head *omfs_get_bucket(struct inode *dir,
		const char *name, int namelen, int *ofs)
{
	int nbuckets = (dir->i_size - OMFS_DIR_START)/8;
	int block = clus_to_blk(OMFS_SB(dir->i_sb), dir->i_ino);
	int bucket = omfs_hash(name, namelen, nbuckets);

	*ofs = OMFS_DIR_START + bucket * 8;
	return sb_bread(dir->i_sb, block);
}