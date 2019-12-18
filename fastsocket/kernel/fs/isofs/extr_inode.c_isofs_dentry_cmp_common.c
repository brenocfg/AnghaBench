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
struct qstr {int len; char* name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int isofs_dentry_cmp_common(struct dentry *dentry, struct qstr *a,
					struct qstr *b, int ms)
{
	int alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = a->len;
	blen = b->len;
	if (ms) {
		while (alen && a->name[alen-1] == '.')
			alen--;
		while (blen && b->name[blen-1] == '.')
			blen--;
	}
	if (alen == blen) {
		if (strncmp(a->name, b->name, alen) == 0)
			return 0;
	}
	return 1;
}