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
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 unsigned int* hpfs_map_4sectors (struct super_block*,int /*<<< orphan*/ ,struct quad_buffer_head*,int) ; 

unsigned hpfs_count_one_bitmap(struct super_block *s, secno secno)
{
	struct quad_buffer_head qbh;
	unsigned *bits;
	unsigned i, count;
	if (!(bits = hpfs_map_4sectors(s, secno, &qbh, 4))) return 0;
	count = 0;
	for (i = 0; i < 2048 / sizeof(unsigned); i++) {
		unsigned b; 
		if (!bits[i]) continue;
		for (b = bits[i]; b; b>>=1) count += b & 1;
	}
	hpfs_brelse4(&qbh);
	return count;
}