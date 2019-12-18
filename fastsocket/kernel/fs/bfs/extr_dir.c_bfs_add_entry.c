#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct inode {int i_size; void* i_mtime; void* i_ctime; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bfs_dirent {unsigned char* name; scalar_t__ ino; } ;
struct TYPE_2__ {int i_sblock; int i_eblock; } ;

/* Variables and functions */
 int BFS_BSIZE ; 
 scalar_t__ BFS_DIRENT_SIZE ; 
 TYPE_1__* BFS_I (struct inode*) ; 
 int BFS_NAMELEN ; 
 void* CURRENT_TIME_SEC ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bfs_add_entry(struct inode *dir, const unsigned char *name,
							int namelen, int ino)
{
	struct buffer_head *bh;
	struct bfs_dirent *de;
	int block, sblock, eblock, off, pos;
	int i;

	dprintf("name=%s, namelen=%d\n", name, namelen);

	if (!namelen)
		return -ENOENT;
	if (namelen > BFS_NAMELEN)
		return -ENAMETOOLONG;

	sblock = BFS_I(dir)->i_sblock;
	eblock = BFS_I(dir)->i_eblock;
	for (block = sblock; block <= eblock; block++) {
		bh = sb_bread(dir->i_sb, block);
		if (!bh)
			return -ENOSPC;
		for (off = 0; off < BFS_BSIZE; off += BFS_DIRENT_SIZE) {
			de = (struct bfs_dirent *)(bh->b_data + off);
			if (!de->ino) {
				pos = (block - sblock) * BFS_BSIZE + off;
				if (pos >= dir->i_size) {
					dir->i_size += BFS_DIRENT_SIZE;
					dir->i_ctime = CURRENT_TIME_SEC;
				}
				dir->i_mtime = CURRENT_TIME_SEC;
				mark_inode_dirty(dir);
				de->ino = cpu_to_le16((u16)ino);
				for (i = 0; i < BFS_NAMELEN; i++)
					de->name[i] =
						(i < namelen) ? name[i] : 0;
				mark_buffer_dirty_inode(bh, dir);
				brelse(bh);
				return 0;
			}
		}
		brelse(bh);
	}
	return -ENOSPC;
}