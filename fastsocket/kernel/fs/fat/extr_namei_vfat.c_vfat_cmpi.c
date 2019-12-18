#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qstr {int /*<<< orphan*/  name; } ;
struct nls_table {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {struct nls_table* nls_io; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 TYPE_2__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ nls_strnicmp (struct nls_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int vfat_striptail_len (struct qstr*) ; 

__attribute__((used)) static int vfat_cmpi(struct dentry *dentry, struct qstr *a, struct qstr *b)
{
	struct nls_table *t = MSDOS_SB(dentry->d_inode->i_sb)->nls_io;
	unsigned int alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = vfat_striptail_len(a);
	blen = vfat_striptail_len(b);
	if (alen == blen) {
		if (nls_strnicmp(t, a->name, b->name, alen) == 0)
			return 0;
	}
	return 1;
}