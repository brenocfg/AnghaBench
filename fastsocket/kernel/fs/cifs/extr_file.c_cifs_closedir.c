#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct cifsFileInfo* private_data; } ;
struct cifs_tcon {int dummy; } ;
struct TYPE_2__ {char* ntwrk_buf_start; scalar_t__ smallBuf; int /*<<< orphan*/  endOfSearch; } ;
struct cifsFileInfo {int invalidHandle; int /*<<< orphan*/  tlink; TYPE_1__ srch_inf; int /*<<< orphan*/  netfid; } ;

/* Variables and functions */
 int CIFSFindClose (int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_buf_release (char*) ; 
 int /*<<< orphan*/  cifs_file_list_lock ; 
 int /*<<< orphan*/  cifs_put_tlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_small_buf_release (char*) ; 
 int /*<<< orphan*/  kfree (struct cifsFileInfo*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

int cifs_closedir(struct inode *inode, struct file *file)
{
	int rc = 0;
	int xid;
	struct cifsFileInfo *pCFileStruct = file->private_data;
	char *ptmp;

	cFYI(1, "Closedir inode = 0x%p", inode);

	xid = GetXid();

	if (pCFileStruct) {
		struct cifs_tcon *pTcon = tlink_tcon(pCFileStruct->tlink);

		cFYI(1, "Freeing private data in close dir");
		spin_lock(&cifs_file_list_lock);
		if (!pCFileStruct->srch_inf.endOfSearch &&
		    !pCFileStruct->invalidHandle) {
			pCFileStruct->invalidHandle = true;
			spin_unlock(&cifs_file_list_lock);
			rc = CIFSFindClose(xid, pTcon, pCFileStruct->netfid);
			cFYI(1, "Closing uncompleted readdir with rc %d",
				 rc);
			/* not much we can do if it fails anyway, ignore rc */
			rc = 0;
		} else
			spin_unlock(&cifs_file_list_lock);
		ptmp = pCFileStruct->srch_inf.ntwrk_buf_start;
		if (ptmp) {
			cFYI(1, "closedir free smb buf in srch struct");
			pCFileStruct->srch_inf.ntwrk_buf_start = NULL;
			if (pCFileStruct->srch_inf.smallBuf)
				cifs_small_buf_release(ptmp);
			else
				cifs_buf_release(ptmp);
		}
		cifs_put_tlink(pCFileStruct->tlink);
		kfree(file->private_data);
		file->private_data = NULL;
	}
	/* BB can we lock the filestruct while this is going on? */
	FreeXid(xid);
	return rc;
}