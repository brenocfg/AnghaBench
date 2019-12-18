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
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct fnode {void* ea_secno; int ea_size_l; int ea_anode; int ea_offs; int ea_size_s; int /*<<< orphan*/  acl_size_s; } ;
struct extended_attribute {int valuelen; int namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  anode; scalar_t__ indirect; } ;
struct buffer_head {int dummy; } ;
typedef  void* secno ;
typedef  scalar_t__ fnode_secno ;
struct TYPE_2__ {int i_ea_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ea_data (struct extended_attribute*) ; 
 int ea_len (struct extended_attribute*) ; 
 int /*<<< orphan*/  ea_sec (struct extended_attribute*) ; 
 struct extended_attribute* fnode_ea (struct fnode*) ; 
 struct extended_attribute* fnode_end_ea (struct fnode*) ; 
 int hpfs_add_sector_to_btree (struct super_block*,void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hpfs_alloc_if_possible (struct super_block*,void*) ; 
 void* hpfs_alloc_sector (struct super_block*,scalar_t__,int,int,int) ; 
 scalar_t__ hpfs_ea_read (struct super_block*,void*,int,unsigned int,int,char*) ; 
 scalar_t__ hpfs_ea_write (struct super_block*,void*,int,int,int,...) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  hpfs_free_sectors (struct super_block*,void*,int) ; 
 void* hpfs_get_sector (struct super_block*,void*,struct buffer_head**) ; 
 TYPE_1__* hpfs_i (struct inode*) ; 
 void* hpfs_map_sector (struct super_block*,void*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  hpfs_truncate_btree (struct super_block*,void*,int,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 struct extended_attribute* next_ea (struct extended_attribute*) ; 
 int /*<<< orphan*/  set_indirect_ea (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

void hpfs_set_ea(struct inode *inode, struct fnode *fnode, char *key, char *data, int size)
{
	fnode_secno fno = inode->i_ino;
	struct super_block *s = inode->i_sb;
	unsigned pos;
	int ano, len;
	secno a;
	unsigned char h[4];
	struct extended_attribute *ea;
	struct extended_attribute *ea_end = fnode_end_ea(fnode);
	for (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		if (!strcmp(ea->name, key)) {
			if (ea->indirect) {
				if (ea_len(ea) == size)
					set_indirect_ea(s, ea->anode, ea_sec(ea), data, size);
			} else if (ea->valuelen == size) {
				memcpy(ea_data(ea), data, size);
			}
			return;
		}
	a = fnode->ea_secno;
	len = fnode->ea_size_l;
	ano = fnode->ea_anode;
	pos = 0;
	while (pos < len) {
		char ex[4 + 255 + 1 + 8];
		ea = (struct extended_attribute *)ex;
		if (pos + 4 > len) {
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			return;
		}
		if (hpfs_ea_read(s, a, ano, pos, 4, ex)) return;
		if (hpfs_ea_read(s, a, ano, pos + 4, ea->namelen + 1 + (ea->indirect ? 8 : 0), ex + 4))
			return;
		if (!strcmp(ea->name, key)) {
			if (ea->indirect) {
				if (ea_len(ea) == size)
					set_indirect_ea(s, ea->anode, ea_sec(ea), data, size);
			}
			else {
				if (ea->valuelen == size)
					hpfs_ea_write(s, a, ano, pos + 4 + ea->namelen + 1, size, data);
			}
			return;
		}
		pos += ea->namelen + ea->valuelen + 5;
	}
	if (!fnode->ea_offs) {
		/*if (fnode->ea_size_s) {
			hpfs_error(s, "fnode %08x: ea_size_s == %03x, ea_offs == 0",
				inode->i_ino, fnode->ea_size_s);
			return;
		}*/
		fnode->ea_offs = 0xc4;
	}
	if (fnode->ea_offs < 0xc4 || fnode->ea_offs + fnode->acl_size_s + fnode->ea_size_s > 0x200) {
		hpfs_error(s, "fnode %08lx: ea_offs == %03x, ea_size_s == %03x",
			(unsigned long)inode->i_ino,
			fnode->ea_offs, fnode->ea_size_s);
		return;
	}
	if ((fnode->ea_size_s || !fnode->ea_size_l) &&
	     fnode->ea_offs + fnode->acl_size_s + fnode->ea_size_s + strlen(key) + size + 5 <= 0x200) {
		ea = fnode_end_ea(fnode);
		*(char *)ea = 0;
		ea->namelen = strlen(key);
		ea->valuelen = size;
		strcpy(ea->name, key);
		memcpy(ea_data(ea), data, size);
		fnode->ea_size_s += strlen(key) + size + 5;
		goto ret;
	}
	/* Most the code here is 99.9993422% unused. I hope there are no bugs.
	   But what .. HPFS.IFS has also bugs in ea management. */
	if (fnode->ea_size_s && !fnode->ea_size_l) {
		secno n;
		struct buffer_head *bh;
		char *data;
		if (!(n = hpfs_alloc_sector(s, fno, 1, 0, 1))) return;
		if (!(data = hpfs_get_sector(s, n, &bh))) {
			hpfs_free_sectors(s, n, 1);
			return;
		}
		memcpy(data, fnode_ea(fnode), fnode->ea_size_s);
		fnode->ea_size_l = fnode->ea_size_s;
		fnode->ea_size_s = 0;
		fnode->ea_secno = n;
		fnode->ea_anode = 0;
		mark_buffer_dirty(bh);
		brelse(bh);
	}
	pos = fnode->ea_size_l + 5 + strlen(key) + size;
	len = (fnode->ea_size_l + 511) >> 9;
	if (pos >= 30000) goto bail;
	while (((pos + 511) >> 9) > len) {
		if (!len) {
			if (!(fnode->ea_secno = hpfs_alloc_sector(s, fno, 1, 0, 1)))
				goto bail;
			fnode->ea_anode = 0;
			len++;
		} else if (!fnode->ea_anode) {
			if (hpfs_alloc_if_possible(s, fnode->ea_secno + len)) {
				len++;
			} else {
				/* Aargh... don't know how to create ea anodes :-( */
				/*struct buffer_head *bh;
				struct anode *anode;
				anode_secno a_s;
				if (!(anode = hpfs_alloc_anode(s, fno, &a_s, &bh)))
					goto bail;
				anode->up = fno;
				anode->btree.fnode_parent = 1;
				anode->btree.n_free_nodes--;
				anode->btree.n_used_nodes++;
				anode->btree.first_free += 12;
				anode->u.external[0].disk_secno = fnode->ea_secno;
				anode->u.external[0].file_secno = 0;
				anode->u.external[0].length = len;
				mark_buffer_dirty(bh);
				brelse(bh);
				fnode->ea_anode = 1;
				fnode->ea_secno = a_s;*/
				secno new_sec;
				int i;
				if (!(new_sec = hpfs_alloc_sector(s, fno, 1, 1 - ((pos + 511) >> 9), 1)))
					goto bail;
				for (i = 0; i < len; i++) {
					struct buffer_head *bh1, *bh2;
					void *b1, *b2;
					if (!(b1 = hpfs_map_sector(s, fnode->ea_secno + i, &bh1, len - i - 1))) {
						hpfs_free_sectors(s, new_sec, (pos + 511) >> 9);
						goto bail;
					}
					if (!(b2 = hpfs_get_sector(s, new_sec + i, &bh2))) {
						brelse(bh1);
						hpfs_free_sectors(s, new_sec, (pos + 511) >> 9);
						goto bail;
					}
					memcpy(b2, b1, 512);
					brelse(bh1);
					mark_buffer_dirty(bh2);
					brelse(bh2);
				}
				hpfs_free_sectors(s, fnode->ea_secno, len);
				fnode->ea_secno = new_sec;
				len = (pos + 511) >> 9;
			}
		}
		if (fnode->ea_anode) {
			if (hpfs_add_sector_to_btree(s, fnode->ea_secno,
						     0, len) != -1) {
				len++;
			} else {
				goto bail;
			}
		}
	}
	h[0] = 0;
	h[1] = strlen(key);
	h[2] = size & 0xff;
	h[3] = size >> 8;
	if (hpfs_ea_write(s, fnode->ea_secno, fnode->ea_anode, fnode->ea_size_l, 4, h)) goto bail;
	if (hpfs_ea_write(s, fnode->ea_secno, fnode->ea_anode, fnode->ea_size_l + 4, h[1] + 1, key)) goto bail;
	if (hpfs_ea_write(s, fnode->ea_secno, fnode->ea_anode, fnode->ea_size_l + 5 + h[1], size, data)) goto bail;
	fnode->ea_size_l = pos;
	ret:
	hpfs_i(inode)->i_ea_size += 5 + strlen(key) + size;
	return;
	bail:
	if (fnode->ea_secno)
		if (fnode->ea_anode) hpfs_truncate_btree(s, fnode->ea_secno, 1, (fnode->ea_size_l + 511) >> 9);
		else hpfs_free_sectors(s, fnode->ea_secno + ((fnode->ea_size_l + 511) >> 9), len - ((fnode->ea_size_l + 511) >> 9));
	else fnode->ea_secno = fnode->ea_size_l = 0;
}