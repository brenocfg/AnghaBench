#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct quad_buffer_head {void* data; TYPE_1__** bh; } ;
struct TYPE_3__ {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  hpfs_get_sector (struct super_block*,unsigned int,TYPE_1__**) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

void *hpfs_get_4sectors(struct super_block *s, unsigned secno,
                          struct quad_buffer_head *qbh)
{
	cond_resched();

	if (secno & 3) {
		printk("HPFS: hpfs_get_4sectors: unaligned read\n");
		return NULL;
	}

	/*return hpfs_map_4sectors(s, secno, qbh, 0);*/
	if (!(qbh->data = kmalloc(2048, GFP_NOFS))) {
		printk("HPFS: hpfs_get_4sectors: out of memory\n");
		return NULL;
	}
	if (!(hpfs_get_sector(s, secno, &qbh->bh[0]))) goto bail0;
	if (!(hpfs_get_sector(s, secno + 1, &qbh->bh[1]))) goto bail1;
	if (!(hpfs_get_sector(s, secno + 2, &qbh->bh[2]))) goto bail2;
	if (!(hpfs_get_sector(s, secno + 3, &qbh->bh[3]))) goto bail3;
	memcpy(qbh->data, qbh->bh[0]->b_data, 512);
	memcpy(qbh->data + 512, qbh->bh[1]->b_data, 512);
	memcpy(qbh->data + 2*512, qbh->bh[2]->b_data, 512);
	memcpy(qbh->data + 3*512, qbh->bh[3]->b_data, 512);
	return qbh->data;

	bail3:	brelse(qbh->bh[2]);
	bail2:	brelse(qbh->bh[1]);
	bail1:	brelse(qbh->bh[0]);
	bail0:
	return NULL;
}