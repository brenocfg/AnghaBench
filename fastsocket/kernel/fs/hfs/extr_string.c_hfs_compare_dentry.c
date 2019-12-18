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
struct qstr {int len; unsigned char* name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int HFS_NAMELEN ; 
 scalar_t__* caseorder ; 

int hfs_compare_dentry(struct dentry *dentry, struct qstr *s1, struct qstr *s2)
{
	const unsigned char *n1, *n2;
	int len;

	len = s1->len;
	if (len >= HFS_NAMELEN) {
		if (s2->len < HFS_NAMELEN)
			return 1;
		len = HFS_NAMELEN;
	} else if (len != s2->len)
		return 1;

	n1 = s1->name;
	n2 = s2->name;
	while (len--) {
		if (caseorder[*n1++] != caseorder[*n2++])
			return 1;
	}
	return 0;
}