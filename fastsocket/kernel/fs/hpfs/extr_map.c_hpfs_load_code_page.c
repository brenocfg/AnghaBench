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
struct code_page_directory {scalar_t__ magic; TYPE_1__* array; int /*<<< orphan*/  n_code_pages; } ;
struct code_page_data {int* offs; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  secno ;
struct TYPE_2__ {unsigned int index; int /*<<< orphan*/  code_page_data; } ;

/* Variables and functions */
 scalar_t__ CP_DIR_MAGIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* hpfs_map_sector (struct super_block*,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ ) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

char *hpfs_load_code_page(struct super_block *s, secno cps)
{
	struct buffer_head *bh;
	secno cpds;
	unsigned cpi;
	unsigned char *ptr;
	unsigned char *cp_table;
	int i;
	struct code_page_data *cpd;
	struct code_page_directory *cp = hpfs_map_sector(s, cps, &bh, 0);
	if (!cp) return NULL;
	if (cp->magic != CP_DIR_MAGIC) {
		printk("HPFS: Code page directory magic doesn't match (magic = %08x)\n", cp->magic);
		brelse(bh);
		return NULL;
	}
	if (!cp->n_code_pages) {
		printk("HPFS: n_code_pages == 0\n");
		brelse(bh);
		return NULL;
	}
	cpds = cp->array[0].code_page_data;
	cpi = cp->array[0].index;
	brelse(bh);

	if (cpi >= 3) {
		printk("HPFS: Code page index out of array\n");
		return NULL;
	}
	
	if (!(cpd = hpfs_map_sector(s, cpds, &bh, 0))) return NULL;
	if ((unsigned)cpd->offs[cpi] > 0x178) {
		printk("HPFS: Code page index out of sector\n");
		brelse(bh);
		return NULL;
	}
	ptr = (char *)cpd + cpd->offs[cpi] + 6;
	if (!(cp_table = kmalloc(256, GFP_KERNEL))) {
		printk("HPFS: out of memory for code page table\n");
		brelse(bh);
		return NULL;
	}
	memcpy(cp_table, ptr, 128);
	brelse(bh);

	/* Try to build lowercasing table from uppercasing one */

	for (i=128; i<256; i++) cp_table[i]=i;
	for (i=128; i<256; i++) if (cp_table[i-128]!=i && cp_table[i-128]>=128)
		cp_table[cp_table[i-128]] = i;
	
	return cp_table;
}