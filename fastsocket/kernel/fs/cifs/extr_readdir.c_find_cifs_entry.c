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
struct smb_hdr {int dummy; } ;
struct file {scalar_t__ f_pos; struct cifsFileInfo* private_data; } ;
struct cifs_tcon {int dummy; } ;
struct TYPE_2__ {scalar_t__ index_of_last_entry; int entries_in_buffer; char* ntwrk_buf_start; char* srch_entries_start; int /*<<< orphan*/  info_level; int /*<<< orphan*/  last_entry; int /*<<< orphan*/  endOfSearch; scalar_t__ smallBuf; } ;
struct cifsFileInfo {int invalidHandle; TYPE_1__ srch_inf; int /*<<< orphan*/  netfid; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSFindClose (int const,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int CIFSFindNext (int const,struct cifs_tcon*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  cERROR (int,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_buf_release (char*) ; 
 int /*<<< orphan*/  cifs_file_list_lock ; 
 int /*<<< orphan*/  cifs_save_resume_key (int /*<<< orphan*/ ,struct cifsFileInfo*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (char*) ; 
 int /*<<< orphan*/  dump_cifs_file_struct (struct file*,char*) ; 
 int initiate_cifs_search (int const,struct file*) ; 
 scalar_t__ is_dir_changed (struct file*) ; 
 char* nxt_dir_entry (char*,char*,int /*<<< orphan*/ ) ; 
 int smbCalcSize (struct smb_hdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_cifs_entry(const int xid, struct cifs_tcon *pTcon,
	struct file *file, char **ppCurrentEntry, int *num_to_ret)
{
	int rc = 0;
	int pos_in_buf = 0;
	loff_t first_entry_in_buffer;
	loff_t index_to_find = file->f_pos;
	struct cifsFileInfo *cifsFile = file->private_data;
	/* check if index in the buffer */

	if ((cifsFile == NULL) || (ppCurrentEntry == NULL) ||
	   (num_to_ret == NULL))
		return -ENOENT;

	*ppCurrentEntry = NULL;
	first_entry_in_buffer =
		cifsFile->srch_inf.index_of_last_entry -
			cifsFile->srch_inf.entries_in_buffer;

	/* if first entry in buf is zero then is first buffer
	in search response data which means it is likely . and ..
	will be in this buffer, although some servers do not return
	. and .. for the root of a drive and for those we need
	to start two entries earlier */

	dump_cifs_file_struct(file, "In fce ");
	if (((index_to_find < cifsFile->srch_inf.index_of_last_entry) &&
	     is_dir_changed(file)) ||
	   (index_to_find < first_entry_in_buffer)) {
		/* close and restart search */
		cFYI(1, "search backing up - close and restart search");
		spin_lock(&cifs_file_list_lock);
		if (!cifsFile->srch_inf.endOfSearch &&
		    !cifsFile->invalidHandle) {
			cifsFile->invalidHandle = true;
			spin_unlock(&cifs_file_list_lock);
			CIFSFindClose(xid, pTcon, cifsFile->netfid);
		} else
			spin_unlock(&cifs_file_list_lock);
		if (cifsFile->srch_inf.ntwrk_buf_start) {
			cFYI(1, "freeing SMB ff cache buf on search rewind");
			if (cifsFile->srch_inf.smallBuf)
				cifs_small_buf_release(cifsFile->srch_inf.
						ntwrk_buf_start);
			else
				cifs_buf_release(cifsFile->srch_inf.
						ntwrk_buf_start);
			cifsFile->srch_inf.ntwrk_buf_start = NULL;
		}
		rc = initiate_cifs_search(xid, file);
		if (rc) {
			cFYI(1, "error %d reinitiating a search on rewind",
				 rc);
			return rc;
		}
		cifs_save_resume_key(cifsFile->srch_inf.last_entry, cifsFile);
	}

	while ((index_to_find >= cifsFile->srch_inf.index_of_last_entry) &&
	      (rc == 0) && !cifsFile->srch_inf.endOfSearch) {
		cFYI(1, "calling findnext2");
		rc = CIFSFindNext(xid, pTcon, cifsFile->netfid,
				  &cifsFile->srch_inf);
		cifs_save_resume_key(cifsFile->srch_inf.last_entry, cifsFile);
		if (rc)
			return -ENOENT;
	}
	if (index_to_find < cifsFile->srch_inf.index_of_last_entry) {
		/* we found the buffer that contains the entry */
		/* scan and find it */
		int i;
		char *current_entry;
		char *end_of_smb = cifsFile->srch_inf.ntwrk_buf_start +
			smbCalcSize((struct smb_hdr *)
				cifsFile->srch_inf.ntwrk_buf_start);

		current_entry = cifsFile->srch_inf.srch_entries_start;
		first_entry_in_buffer = cifsFile->srch_inf.index_of_last_entry
					- cifsFile->srch_inf.entries_in_buffer;
		pos_in_buf = index_to_find - first_entry_in_buffer;
		cFYI(1, "found entry - pos_in_buf %d", pos_in_buf);

		for (i = 0; (i < (pos_in_buf)) && (current_entry != NULL); i++) {
			/* go entry by entry figuring out which is first */
			current_entry = nxt_dir_entry(current_entry, end_of_smb,
						cifsFile->srch_inf.info_level);
		}
		if ((current_entry == NULL) && (i < pos_in_buf)) {
			/* BB fixme - check if we should flag this error */
			cERROR(1, "reached end of buf searching for pos in buf"
			  " %d index to find %lld rc %d",
			  pos_in_buf, index_to_find, rc);
		}
		rc = 0;
		*ppCurrentEntry = current_entry;
	} else {
		cFYI(1, "index not in buffer - could not findnext into it");
		return 0;
	}

	if (pos_in_buf >= cifsFile->srch_inf.entries_in_buffer) {
		cFYI(1, "can not return entries pos_in_buf beyond last");
		*num_to_ret = 0;
	} else
		*num_to_ret = cifsFile->srch_inf.entries_in_buffer - pos_in_buf;

	return rc;
}