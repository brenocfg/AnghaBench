#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sqnum; } ;
struct ubifs_dent_node {char* name; int /*<<< orphan*/  key; int /*<<< orphan*/  type; int /*<<< orphan*/  inum; int /*<<< orphan*/  nlen; TYPE_3__ ch; } ;
struct qstr {char* name; int len; } ;
struct inode {scalar_t__ i_ino; TYPE_1__* i_sb; } ;
struct TYPE_7__ {TYPE_5__* dentry; } ;
struct file {int f_pos; struct ubifs_dent_node* private_data; TYPE_2__ f_path; } ;
typedef  int (* filldir_t ) (void*,char*,int,int,scalar_t__,int /*<<< orphan*/ ) ;
struct TYPE_10__ {struct inode* d_inode; } ;
struct TYPE_9__ {scalar_t__ creat_sqnum; } ;
struct TYPE_6__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct ubifs_dent_node*) ; 
 int PTR_ERR (struct ubifs_dent_node*) ; 
 int UBIFS_S_KEY_HASH_MASK ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dbg_gen (char*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  dent_key_init_hash (struct ubifs_info*,union ubifs_key*,scalar_t__,int) ; 
 void* key_hash_flash (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_read (struct ubifs_info*,int /*<<< orphan*/ *,union ubifs_key*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowest_dent_key (struct ubifs_info*,union ubifs_key*,scalar_t__) ; 
 scalar_t__ parent_ino (TYPE_5__*) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int) ; 
 TYPE_4__* ubifs_inode (struct inode*) ; 
 struct ubifs_dent_node* ubifs_tnc_next_ent (struct ubifs_info*,union ubifs_key*,struct qstr*) ; 
 int /*<<< orphan*/  vfs_dent_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ubifs_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	int err, over = 0;
	struct qstr nm;
	union ubifs_key key;
	struct ubifs_dent_node *dent;
	struct inode *dir = file->f_path.dentry->d_inode;
	struct ubifs_info *c = dir->i_sb->s_fs_info;

	dbg_gen("dir ino %lu, f_pos %#llx", dir->i_ino, file->f_pos);

	if (file->f_pos > UBIFS_S_KEY_HASH_MASK || file->f_pos == 2)
		/*
		 * The directory was seek'ed to a senseless position or there
		 * are no more entries.
		 */
		return 0;

	/* File positions 0 and 1 correspond to "." and ".." */
	if (file->f_pos == 0) {
		ubifs_assert(!file->private_data);
		over = filldir(dirent, ".", 1, 0, dir->i_ino, DT_DIR);
		if (over)
			return 0;
		file->f_pos = 1;
	}

	if (file->f_pos == 1) {
		ubifs_assert(!file->private_data);
		over = filldir(dirent, "..", 2, 1,
			       parent_ino(file->f_path.dentry), DT_DIR);
		if (over)
			return 0;

		/* Find the first entry in TNC and save it */
		lowest_dent_key(c, &key, dir->i_ino);
		nm.name = NULL;
		dent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_ERR(dent)) {
			err = PTR_ERR(dent);
			goto out;
		}

		file->f_pos = key_hash_flash(c, &dent->key);
		file->private_data = dent;
	}

	dent = file->private_data;
	if (!dent) {
		/*
		 * The directory was seek'ed to and is now readdir'ed.
		 * Find the entry corresponding to @file->f_pos or the
		 * closest one.
		 */
		dent_key_init_hash(c, &key, dir->i_ino, file->f_pos);
		nm.name = NULL;
		dent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_ERR(dent)) {
			err = PTR_ERR(dent);
			goto out;
		}
		file->f_pos = key_hash_flash(c, &dent->key);
		file->private_data = dent;
	}

	while (1) {
		dbg_gen("feed '%s', ino %llu, new f_pos %#x",
			dent->name, (unsigned long long)le64_to_cpu(dent->inum),
			key_hash_flash(c, &dent->key));
		ubifs_assert(le64_to_cpu(dent->ch.sqnum) >
			     ubifs_inode(dir)->creat_sqnum);

		nm.len = le16_to_cpu(dent->nlen);
		over = filldir(dirent, dent->name, nm.len, file->f_pos,
			       le64_to_cpu(dent->inum),
			       vfs_dent_type(dent->type));
		if (over)
			return 0;

		/* Switch to the next entry */
		key_read(c, &dent->key, &key);
		nm.name = dent->name;
		dent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_ERR(dent)) {
			err = PTR_ERR(dent);
			goto out;
		}

		kfree(file->private_data);
		file->f_pos = key_hash_flash(c, &dent->key);
		file->private_data = dent;
		cond_resched();
	}

out:
	if (err != -ENOENT) {
		ubifs_err("cannot find next direntry, error %d", err);
		return err;
	}

	kfree(file->private_data);
	file->private_data = NULL;
	file->f_pos = 2;
	return 0;
}