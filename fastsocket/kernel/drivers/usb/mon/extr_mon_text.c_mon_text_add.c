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
struct usb_bus {int busnum; } ;
struct mon_bus {struct dentry* dent_t; struct dentry* dent_u; struct dentry* dent_s; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct mon_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 int /*<<< orphan*/  mon_dir ; 
 int /*<<< orphan*/  mon_fops_stat ; 
 int /*<<< orphan*/  mon_fops_text_t ; 
 int /*<<< orphan*/  mon_fops_text_u ; 
 int snprintf (char*,int,char*,int) ; 

int mon_text_add(struct mon_bus *mbus, const struct usb_bus *ubus)
{
	struct dentry *d;
	enum { NAMESZ = 10 };
	char name[NAMESZ];
	int busnum = ubus? ubus->busnum: 0;
	int rc;

	if (ubus != NULL) {
		rc = snprintf(name, NAMESZ, "%dt", busnum);
		if (rc <= 0 || rc >= NAMESZ)
			goto err_print_t;
		d = debugfs_create_file(name, 0600, mon_dir, mbus,
							     &mon_fops_text_t);
		if (d == NULL)
			goto err_create_t;
		mbus->dent_t = d;
	}

	rc = snprintf(name, NAMESZ, "%du", busnum);
	if (rc <= 0 || rc >= NAMESZ)
		goto err_print_u;
	d = debugfs_create_file(name, 0600, mon_dir, mbus, &mon_fops_text_u);
	if (d == NULL)
		goto err_create_u;
	mbus->dent_u = d;

	rc = snprintf(name, NAMESZ, "%ds", busnum);
	if (rc <= 0 || rc >= NAMESZ)
		goto err_print_s;
	d = debugfs_create_file(name, 0600, mon_dir, mbus, &mon_fops_stat);
	if (d == NULL)
		goto err_create_s;
	mbus->dent_s = d;

	return 1;

err_create_s:
err_print_s:
	debugfs_remove(mbus->dent_u);
	mbus->dent_u = NULL;
err_create_u:
err_print_u:
	if (ubus != NULL) {
		debugfs_remove(mbus->dent_t);
		mbus->dent_t = NULL;
	}
err_create_t:
err_print_t:
	return 0;
}