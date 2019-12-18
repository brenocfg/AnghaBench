#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {int f_mode; struct cifsFileInfo* private_data; int /*<<< orphan*/  f_flags; TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;
struct cifsInodeInfo {int /*<<< orphan*/  openFileList; } ;
struct cifsFileInfo {int count; int invalidHandle; int /*<<< orphan*/  flist; int /*<<< orphan*/  tlist; int /*<<< orphan*/  oplock_break; int /*<<< orphan*/  llist; int /*<<< orphan*/  lock_mutex; int /*<<< orphan*/  fh_mutex; int /*<<< orphan*/  tlink; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  dentry; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; int /*<<< orphan*/  netfid; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_5__ {int /*<<< orphan*/  openFileList; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_file_list_lock ; 
 int /*<<< orphan*/  cifs_get_tlink (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_oplock_break_ops ; 
 int /*<<< orphan*/  cifs_sb_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_set_oplock_level (struct cifsInodeInfo*,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct cifsFileInfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* tlink_tcon (struct tcon_link*) ; 
 int /*<<< orphan*/  vslow_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct cifsFileInfo *
cifs_new_fileinfo(__u16 fileHandle, struct file *file,
		  struct tcon_link *tlink, __u32 oplock)
{
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	struct cifsInodeInfo *pCifsInode = CIFS_I(inode);
	struct cifsFileInfo *pCifsFile;

	pCifsFile = kzalloc(sizeof(struct cifsFileInfo), GFP_KERNEL);
	if (pCifsFile == NULL)
		return pCifsFile;

	pCifsFile->count = 1;
	pCifsFile->netfid = fileHandle;
	pCifsFile->pid = current->tgid;
	pCifsFile->uid = current_fsuid();
	pCifsFile->dentry = dget(dentry);
	pCifsFile->f_flags = file->f_flags;
	pCifsFile->invalidHandle = false;
	pCifsFile->tlink = cifs_get_tlink(tlink);
	mutex_init(&pCifsFile->fh_mutex);
	mutex_init(&pCifsFile->lock_mutex);
	INIT_LIST_HEAD(&pCifsFile->llist);
	vslow_work_init(&pCifsFile->oplock_break, &cifs_oplock_break_ops);

	cifs_sb_active(inode->i_sb);

	spin_lock(&cifs_file_list_lock);
	list_add(&pCifsFile->tlist, &(tlink_tcon(tlink)->openFileList));
	/* if readable file instance put first in list*/
	if (file->f_mode & FMODE_READ)
		list_add(&pCifsFile->flist, &pCifsInode->openFileList);
	else
		list_add_tail(&pCifsFile->flist, &pCifsInode->openFileList);
	spin_unlock(&cifs_file_list_lock);

	cifs_set_oplock_level(pCifsInode, oplock);

	file->private_data = pCifsFile;
	return pCifsFile;
}