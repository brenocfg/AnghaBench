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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 scalar_t__ is_bad (struct dentry*) ; 
 struct dentry** kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dentry* securityfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* securityfs_create_file (char*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  securityfs_remove (struct dentry*) ; 
 int /*<<< orphan*/  tpm_ascii_bios_measurements_ops ; 
 int /*<<< orphan*/  tpm_binary_bios_measurements_ops ; 

struct dentry **tpm_bios_log_setup(char *name)
{
	struct dentry **ret = NULL, *tpm_dir, *bin_file, *ascii_file;

	tpm_dir = securityfs_create_dir(name, NULL);
	if (is_bad(tpm_dir))
		goto out;

	bin_file =
	    securityfs_create_file("binary_bios_measurements",
				   S_IRUSR | S_IRGRP, tpm_dir, NULL,
				   &tpm_binary_bios_measurements_ops);
	if (is_bad(bin_file))
		goto out_tpm;

	ascii_file =
	    securityfs_create_file("ascii_bios_measurements",
				   S_IRUSR | S_IRGRP, tpm_dir, NULL,
				   &tpm_ascii_bios_measurements_ops);
	if (is_bad(ascii_file))
		goto out_bin;

	ret = kmalloc(3 * sizeof(struct dentry *), GFP_KERNEL);
	if (!ret)
		goto out_ascii;

	ret[0] = ascii_file;
	ret[1] = bin_file;
	ret[2] = tpm_dir;

	return ret;

out_ascii:
	securityfs_remove(ascii_file);
out_bin:
	securityfs_remove(bin_file);
out_tpm:
	securityfs_remove(tpm_dir);
out:
	return NULL;
}