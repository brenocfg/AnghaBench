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
struct TYPE_2__ {int /*<<< orphan*/  sb_cp_table; } ;

/* Variables and functions */
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 unsigned char upcase (int /*<<< orphan*/ ,unsigned char) ; 

int hpfs_compare_names(struct super_block *s, unsigned char *n1, unsigned l1,
		       unsigned char *n2, unsigned l2, int last)
{
	unsigned l = l1 < l2 ? l1 : l2;
	unsigned i;
	if (last) return -1;
	for (i = 0; i < l; i++) {
		unsigned char c1 = upcase(hpfs_sb(s)->sb_cp_table,n1[i]);
		unsigned char c2 = upcase(hpfs_sb(s)->sb_cp_table,n2[i]);
		if (c1 < c2) return -1;
		if (c1 > c2) return 1;
	}
	if (l1 < l2) return -1;
	if (l1 > l2) return 1;
	return 0;
}