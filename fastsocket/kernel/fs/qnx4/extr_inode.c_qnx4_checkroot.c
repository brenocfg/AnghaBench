#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_id; } ;
struct qnx4_inode_entry {int /*<<< orphan*/ * di_fname; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  BitMap; TYPE_3__* sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  xtnt_size; int /*<<< orphan*/  xtnt_blk; } ;
struct TYPE_6__ {char* di_fname; TYPE_1__ di_first_xtnt; } ;
struct TYPE_7__ {TYPE_2__ RootDir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QNX4DEBUG (char*) ; 
 int /*<<< orphan*/  QNX4_BMNAME ; 
 int QNX4_DIR_ENTRY_SIZE ; 
 int QNX4_INODES_PER_BLOCK ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct qnx4_inode_entry*,int) ; 
 TYPE_4__* qnx4_sb (struct super_block*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *qnx4_checkroot(struct super_block *sb)
{
	struct buffer_head *bh;
	struct qnx4_inode_entry *rootdir;
	int rd, rl;
	int i, j;
	int found = 0;

	if (*(qnx4_sb(sb)->sb->RootDir.di_fname) != '/') {
		return "no qnx4 filesystem (no root dir).";
	} else {
		QNX4DEBUG(("QNX4 filesystem found on dev %s.\n", sb->s_id));
		rd = le32_to_cpu(qnx4_sb(sb)->sb->RootDir.di_first_xtnt.xtnt_blk) - 1;
		rl = le32_to_cpu(qnx4_sb(sb)->sb->RootDir.di_first_xtnt.xtnt_size);
		for (j = 0; j < rl; j++) {
			bh = sb_bread(sb, rd + j);	/* root dir, first block */
			if (bh == NULL) {
				return "unable to read root entry.";
			}
			for (i = 0; i < QNX4_INODES_PER_BLOCK; i++) {
				rootdir = (struct qnx4_inode_entry *) (bh->b_data + i * QNX4_DIR_ENTRY_SIZE);
				if (rootdir->di_fname != NULL) {
					QNX4DEBUG(("Rootdir entry found : [%s]\n", rootdir->di_fname));
					if (!strncmp(rootdir->di_fname, QNX4_BMNAME, sizeof QNX4_BMNAME)) {
						found = 1;
						qnx4_sb(sb)->BitMap = kmalloc( sizeof( struct qnx4_inode_entry ), GFP_KERNEL );
						if (!qnx4_sb(sb)->BitMap) {
							brelse (bh);
							return "not enough memory for bitmap inode";
						}
						memcpy( qnx4_sb(sb)->BitMap, rootdir, sizeof( struct qnx4_inode_entry ) );	/* keep bitmap inode known */
						break;
					}
				}
			}
			brelse(bh);
			if (found != 0) {
				break;
			}
		}
		if (found == 0) {
			return "bitmap file not found.";
		}
	}
	return NULL;
}