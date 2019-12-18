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
struct super_block {int dummy; } ;
struct diag2fc_data {int /*<<< orphan*/  lcpus; } ;
struct dentry {int /*<<< orphan*/  lcpus; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct diag2fc_data*) ; 
 int PTR_ERR (struct diag2fc_data*) ; 
 int /*<<< orphan*/  diag2fc_free (struct diag2fc_data*) ; 
 struct diag2fc_data* diag2fc_store (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guest_query ; 
 int hpyfs_vm_create_guest (struct super_block*,struct diag2fc_data*,struct diag2fc_data*) ; 
 struct diag2fc_data* hypfs_create_str (struct super_block*,struct diag2fc_data*,char*,char*) ; 
 struct diag2fc_data* hypfs_create_u64 (struct super_block*,struct diag2fc_data*,char*,int /*<<< orphan*/ ) ; 
 struct diag2fc_data* hypfs_mkdir (struct super_block*,struct diag2fc_data*,char*) ; 

int hypfs_vm_create_files(struct super_block *sb, struct dentry *root)
{
	struct dentry *dir, *file;
	struct diag2fc_data *data;
	unsigned int count = 0;
	int rc, i;

	data = diag2fc_store(guest_query, &count, 0);
	if (IS_ERR(data))
		return PTR_ERR(data);

	/* Hpervisor Info */
	dir = hypfs_mkdir(sb, root, "hyp");
	if (IS_ERR(dir)) {
		rc = PTR_ERR(dir);
		goto failed;
	}
	file = hypfs_create_str(sb, dir, "type", "z/VM Hypervisor");
	if (IS_ERR(file)) {
		rc = PTR_ERR(file);
		goto failed;
	}

	/* physical cpus */
	dir = hypfs_mkdir(sb, root, "cpus");
	if (IS_ERR(dir)) {
		rc = PTR_ERR(dir);
		goto failed;
	}
	file = hypfs_create_u64(sb, dir, "count", data->lcpus);
	if (IS_ERR(file)) {
		rc = PTR_ERR(file);
		goto failed;
	}

	/* guests */
	dir = hypfs_mkdir(sb, root, "systems");
	if (IS_ERR(dir)) {
		rc = PTR_ERR(dir);
		goto failed;
	}

	for (i = 0; i < count; i++) {
		rc = hpyfs_vm_create_guest(sb, dir, &(data[i]));
		if (rc)
			goto failed;
	}
	diag2fc_free(data);
	return 0;

failed:
	diag2fc_free(data);
	return rc;
}