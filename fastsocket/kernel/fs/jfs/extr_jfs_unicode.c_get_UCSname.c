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
typedef  int /*<<< orphan*/  wchar_t ;
struct nls_table {int dummy; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct component_name {int namlen; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {struct nls_table* nls_tab; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int JFS_NAME_MAX ; 
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int jfs_strtoUCS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct nls_table*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

int get_UCSname(struct component_name * uniName, struct dentry *dentry)
{
	struct nls_table *nls_tab = JFS_SBI(dentry->d_sb)->nls_tab;
	int length = dentry->d_name.len;

	if (length > JFS_NAME_MAX)
		return -ENAMETOOLONG;

	uniName->name =
	    kmalloc((length + 1) * sizeof(wchar_t), GFP_NOFS);

	if (uniName->name == NULL)
		return -ENOMEM;

	uniName->namlen = jfs_strtoUCS(uniName->name, dentry->d_name.name,
				       length, nls_tab);

	if (uniName->namlen < 0) {
		kfree(uniName->name);
		return uniName->namlen;
	}

	return 0;
}