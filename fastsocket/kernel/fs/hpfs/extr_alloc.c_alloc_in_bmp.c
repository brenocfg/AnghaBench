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
typedef  int secno ;
struct TYPE_2__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,unsigned int,...) ; 
 unsigned int* hpfs_map_bitmap (struct super_block*,int,struct quad_buffer_head*,char*) ; 
 unsigned int* hpfs_map_dnode_bitmap (struct super_block*,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int tstbits (unsigned int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static secno alloc_in_bmp(struct super_block *s, secno near, unsigned n, unsigned forward)
{
	struct quad_buffer_head qbh;
	unsigned *bmp;
	unsigned bs = near & ~0x3fff;
	unsigned nr = (near & 0x3fff) & ~(n - 1);
	/*unsigned mnr;*/
	unsigned i, q;
	int a, b;
	secno ret = 0;
	if (n != 1 && n != 4) {
		hpfs_error(s, "Bad allocation size: %d", n);
		return 0;
	}
	lock_super(s);
	if (bs != ~0x3fff) {
		if (!(bmp = hpfs_map_bitmap(s, near >> 14, &qbh, "aib"))) goto uls;
	} else {
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) goto uls;
	}
	if (!tstbits(bmp, nr, n + forward)) {
		ret = bs + nr;
		goto rt;
	}
	/*if (!tstbits(bmp, nr + n, n + forward)) {
		ret = bs + nr + n;
		goto rt;
	}*/
	q = nr + n; b = 0;
	while ((a = tstbits(bmp, q, n + forward)) != 0) {
		q += a;
		if (n != 1) q = ((q-1)&~(n-1))+n;
		if (!b) {
			if (q>>5 != nr>>5) {
				b = 1;
				q = nr & 0x1f;
			}
		} else if (q > nr) break;
	}
	if (!a) {
		ret = bs + q;
		goto rt;
	}
	nr >>= 5;
	/*for (i = nr + 1; i != nr; i++, i &= 0x1ff) {*/
	i = nr;
	do {
		if (!bmp[i]) goto cont;
		if (n + forward >= 0x3f && bmp[i] != -1) goto cont;
		q = i<<5;
		if (i > 0) {
			unsigned k = bmp[i-1];
			while (k & 0x80000000) {
				q--; k <<= 1;
			}
		}
		if (n != 1) q = ((q-1)&~(n-1))+n;
		while ((a = tstbits(bmp, q, n + forward)) != 0) {
			q += a;
			if (n != 1) q = ((q-1)&~(n-1))+n;
			if (q>>5 > i) break;
		}
		if (!a) {
			ret = bs + q;
			goto rt;
		}
		cont:
		i++, i &= 0x1ff;
	} while (i != nr);
	rt:
	if (ret) {
		if (hpfs_sb(s)->sb_chk && ((ret >> 14) != (bs >> 14) || (bmp[(ret & 0x3fff) >> 5] | ~(((1 << n) - 1) << (ret & 0x1f))) != 0xffffffff)) {
			hpfs_error(s, "Allocation doesn't work! Wanted %d, allocated at %08x", n, ret);
			ret = 0;
			goto b;
		}
		bmp[(ret & 0x3fff) >> 5] &= ~(((1 << n) - 1) << (ret & 0x1f));
		hpfs_mark_4buffers_dirty(&qbh);
	}
	b:
	hpfs_brelse4(&qbh);
	uls:
	unlock_super(s);
	return ret;
}