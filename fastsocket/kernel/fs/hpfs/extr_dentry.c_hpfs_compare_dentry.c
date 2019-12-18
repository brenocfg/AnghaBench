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
struct qstr {unsigned int len; scalar_t__ name; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_adjust_length (char*,unsigned int*) ; 
 scalar_t__ hpfs_chk_name (char*,unsigned int*) ; 
 scalar_t__ hpfs_compare_names (int /*<<< orphan*/ ,char*,unsigned int,char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpfs_compare_dentry(struct dentry *dentry, struct qstr *a, struct qstr *b)
{
	unsigned al=a->len;
	unsigned bl=b->len;
	hpfs_adjust_length((char *)a->name, &al);
	/*hpfs_adjust_length((char *)b->name, &bl);*/
	/* 'a' is the qstr of an already existing dentry, so the name
	 * must be valid. 'b' must be validated first.
	 */

	if (hpfs_chk_name((char *)b->name, &bl)) return 1;
	if (hpfs_compare_names(dentry->d_sb, (char *)a->name, al, (char *)b->name, bl, 0)) return 1;
	return 0;
}