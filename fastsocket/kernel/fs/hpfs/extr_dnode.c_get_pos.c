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
struct hpfs_dirent {int dummy; } ;
struct dnode {scalar_t__ self; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static loff_t get_pos(struct dnode *d, struct hpfs_dirent *fde)
{
	struct hpfs_dirent *de;
	struct hpfs_dirent *de_end = dnode_end_de(d);
	int i = 1;
	for (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) {
		if (de == fde) return ((loff_t) d->self << 4) | (loff_t)i;
		i++;
	}
	printk("HPFS: get_pos: not_found\n");
	return ((loff_t)d->self << 4) | (loff_t)1;
}