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
struct quad_buffer_head {int dummy; } ;
struct TYPE_2__ {int sb_fs_size; int sb_c_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 unsigned int* hpfs_map_bitmap (struct super_block*,int,struct quad_buffer_head*,char*) ; 
 unsigned int* hpfs_map_dnode_bitmap (struct super_block*,struct quad_buffer_head*) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 

int hpfs_check_free_dnodes(struct super_block *s, int n)
{
	int n_bmps = (hpfs_sb(s)->sb_fs_size + 0x4000 - 1) >> 14;
	int b = hpfs_sb(s)->sb_c_bitmap & 0x0fffffff;
	int i, j;
	unsigned *bmp;
	struct quad_buffer_head qbh;
	if ((bmp = hpfs_map_dnode_bitmap(s, &qbh))) {
		for (j = 0; j < 512; j++) {
			unsigned k;
			if (!bmp[j]) continue;
			for (k = bmp[j]; k; k >>= 1) if (k & 1) if (!--n) {
				hpfs_brelse4(&qbh);
				return 0;
			}
		}
	}
	hpfs_brelse4(&qbh);
	i = 0;
	if (hpfs_sb(s)->sb_c_bitmap != -1) {
		bmp = hpfs_map_bitmap(s, b, &qbh, "chkdn1");
		goto chk_bmp;
	}
	chk_next:
	if (i == b) i++;
	if (i >= n_bmps) return 1;
	bmp = hpfs_map_bitmap(s, i, &qbh, "chkdn2");
	chk_bmp:
	if (bmp) {
		for (j = 0; j < 512; j++) {
			unsigned k;
			if (!bmp[j]) continue;
			for (k = 0xf; k; k <<= 4)
				if ((bmp[j] & k) == k) {
					if (!--n) {
						hpfs_brelse4(&qbh);
						return 0;
					}
				}
		}
		hpfs_brelse4(&qbh);
	}
	i++;
	goto chk_next;
}