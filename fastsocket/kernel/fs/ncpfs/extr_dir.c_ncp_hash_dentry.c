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
struct qstr {int len; int /*<<< orphan*/  hash; int /*<<< orphan*/ * name; } ;
struct nls_table {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct nls_table* NCP_IO_TABLE (struct dentry*) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash () ; 
 int /*<<< orphan*/  ncp_case_sensitive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_tolower (struct nls_table*,int /*<<< orphan*/ ) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int 
ncp_hash_dentry(struct dentry *dentry, struct qstr *this)
{
	struct nls_table *t;
	unsigned long hash;
	int i;

	t = NCP_IO_TABLE(dentry);

	if (!ncp_case_sensitive(dentry->d_inode)) {
		hash = init_name_hash();
		for (i=0; i<this->len ; i++)
			hash = partial_name_hash(ncp_tolower(t, this->name[i]),
									hash);
		this->hash = end_name_hash(hash);
	}
	return 0;
}