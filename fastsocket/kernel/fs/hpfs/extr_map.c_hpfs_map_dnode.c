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
struct super_block {int s_flags; } ;
struct quad_buffer_head {int dummy; } ;
struct hpfs_dirent {int length; int namelen; int down; } ;
struct dnode {scalar_t__ magic; unsigned int self; int first_free; } ;
struct TYPE_2__ {int sb_chk; } ;

/* Variables and functions */
 scalar_t__ DNODE_MAGIC ; 
 int /*<<< orphan*/  DNODE_RD_AHEAD ; 
 int MS_RDONLY ; 
 int de_down_pointer (struct hpfs_dirent*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 scalar_t__ hpfs_chk_sectors (struct super_block*,unsigned int,int,char*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,unsigned int,...) ; 
 struct dnode* hpfs_map_4sectors (struct super_block*,unsigned int,struct quad_buffer_head*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

struct dnode *hpfs_map_dnode(struct super_block *s, unsigned secno,
			     struct quad_buffer_head *qbh)
{
	struct dnode *dnode;
	if (hpfs_sb(s)->sb_chk) {
		if (hpfs_chk_sectors(s, secno, 4, "dnode")) return NULL;
		if (secno & 3) {
			hpfs_error(s, "dnode %08x not byte-aligned", secno);
			return NULL;
		}	
	}
	if ((dnode = hpfs_map_4sectors(s, secno, qbh, DNODE_RD_AHEAD)))
		if (hpfs_sb(s)->sb_chk) {
			unsigned p, pp = 0;
			unsigned char *d = (char *)dnode;
			int b = 0;
			if (dnode->magic != DNODE_MAGIC) {
				hpfs_error(s, "bad magic on dnode %08x", secno);
				goto bail;
			}
			if (dnode->self != secno)
				hpfs_error(s, "bad self pointer on dnode %08x self = %08x", secno, dnode->self);
			/* Check dirents - bad dirents would cause infinite
			   loops or shooting to memory */
			if (dnode->first_free > 2048/* || dnode->first_free < 84*/) {
				hpfs_error(s, "dnode %08x has first_free == %08x", secno, dnode->first_free);
				goto bail;
			}
			for (p = 20; p < dnode->first_free; p += d[p] + (d[p+1] << 8)) {
				struct hpfs_dirent *de = (struct hpfs_dirent *)((char *)dnode + p);
				if (de->length > 292 || (de->length < 32) || (de->length & 3) || p + de->length > 2048) {
					hpfs_error(s, "bad dirent size in dnode %08x, dirent %03x, last %03x", secno, p, pp);
					goto bail;
				}
				if (((31 + de->namelen + de->down*4 + 3) & ~3) != de->length) {
					if (((31 + de->namelen + de->down*4 + 3) & ~3) < de->length && s->s_flags & MS_RDONLY) goto ok;
					hpfs_error(s, "namelen does not match dirent size in dnode %08x, dirent %03x, last %03x", secno, p, pp);
					goto bail;
				}
				ok:
				if (hpfs_sb(s)->sb_chk >= 2) b |= 1 << de->down;
				if (de->down) if (de_down_pointer(de) < 0x10) {
					hpfs_error(s, "bad down pointer in dnode %08x, dirent %03x, last %03x", secno, p, pp);
					goto bail;
				}
				pp = p;
				
			}
			if (p != dnode->first_free) {
				hpfs_error(s, "size on last dirent does not match first_free; dnode %08x", secno);
				goto bail;
			}
			if (d[pp + 30] != 1 || d[pp + 31] != 255) {
				hpfs_error(s, "dnode %08x does not end with \\377 entry", secno);
				goto bail;
			}
			if (b == 3) printk("HPFS: warning: unbalanced dnode tree, dnode %08x; see hpfs.txt 4 more info\n", secno);
		}
	return dnode;
	bail:
	hpfs_brelse4(qbh);
	return NULL;
}