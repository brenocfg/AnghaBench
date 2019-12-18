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
struct qstr {int len; int /*<<< orphan*/  hash; int /*<<< orphan*/ * name; } ;
struct nls_table {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_4__ {struct nls_table* local_nls; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 TYPE_2__* CIFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash () ; 
 int /*<<< orphan*/  nls_tolower (struct nls_table*,int /*<<< orphan*/ ) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int cifs_ci_hash(struct dentry *dentry, struct qstr *q)
{
	struct nls_table *codepage = CIFS_SB(dentry->d_inode->i_sb)->local_nls;
	unsigned long hash;
	int i;

	hash = init_name_hash();
	for (i = 0; i < q->len; i++)
		hash = partial_name_hash(nls_tolower(codepage, q->name[i]),
					 hash);
	q->hash = end_name_hash(hash);

	return 0;
}