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
struct qstr {char* name; int /*<<< orphan*/  hash; scalar_t__ len; } ;
struct pohmelfs_sb {int dummy; } ;
struct pohmelfs_name {unsigned int mode; int /*<<< orphan*/  data; int /*<<< orphan*/  hash; scalar_t__ len; int /*<<< orphan*/  ino; } ;
struct pohmelfs_inode {int /*<<< orphan*/  offset_lock; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (struct pohmelfs_name*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pohmelfs_insert_name (struct pohmelfs_inode*,struct pohmelfs_name*) ; 
 struct pohmelfs_name* pohmelfs_name_alloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int pohmelfs_add_dir(struct pohmelfs_sb *psb, struct pohmelfs_inode *parent,
		struct pohmelfs_inode *npi, struct qstr *str, unsigned int mode, int link)
{
	int err = -ENOMEM;
	struct pohmelfs_name *n;

	n = pohmelfs_name_alloc(str->len + 1);
	if (!n)
		goto err_out_exit;

	n->ino = npi->ino;
	n->mode = mode;
	n->len = str->len;
	n->hash = str->hash;
	sprintf(n->data, "%s", str->name);

	mutex_lock(&parent->offset_lock);
	err = pohmelfs_insert_name(parent, n);
	mutex_unlock(&parent->offset_lock);

	if (err) {
		if (err != -EEXIST)
			goto err_out_free;
		kfree(n);
	}

	return 0;

err_out_free:
	kfree(n);
err_out_exit:
	return err;
}