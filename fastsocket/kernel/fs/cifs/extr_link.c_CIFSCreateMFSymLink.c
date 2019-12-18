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
typedef  int /*<<< orphan*/  u8 ;
struct nls_table {int dummy; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; struct nls_table* local_nls; } ;
struct cifs_io_parms {unsigned int length; scalar_t__ offset; struct cifs_tcon* tcon; int /*<<< orphan*/  pid; int /*<<< orphan*/  netfid; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int CIFSFormatMFSymlink (int /*<<< orphan*/ *,unsigned int,char const*) ; 
 int /*<<< orphan*/  CIFSSMBClose (int const,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int CIFSSMBOpen (int const,struct cifs_tcon*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,struct nls_table*,int) ; 
 int CIFSSMBWrite (int const,struct cifs_io_parms*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int CIFS_MF_SYMLINK_FILE_SIZE ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CREATE_NOT_DIR ; 
 int CREATE_OPEN_BACKUP_INTENT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILE_CREATE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
CIFSCreateMFSymLink(const int xid, struct cifs_tcon *tcon,
		    const char *fromName, const char *toName,
		    struct cifs_sb_info *cifs_sb)
{
	int rc;
	int oplock = 0;
	int remap;
	int create_options = CREATE_NOT_DIR;
	__u16 netfid = 0;
	u8 *buf;
	unsigned int bytes_written = 0;
	struct cifs_io_parms io_parms;
	struct nls_table *nls_codepage;

	nls_codepage = cifs_sb->local_nls;
	remap = cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR;

	buf = kmalloc(CIFS_MF_SYMLINK_FILE_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	rc = CIFSFormatMFSymlink(buf, CIFS_MF_SYMLINK_FILE_SIZE, toName);
	if (rc != 0) {
		kfree(buf);
		return rc;
	}

	if (backup_cred(cifs_sb))
		create_options |= CREATE_OPEN_BACKUP_INTENT;

	rc = CIFSSMBOpen(xid, tcon, fromName, FILE_CREATE, GENERIC_WRITE,
			 create_options, &netfid, &oplock, NULL,
			 nls_codepage, remap);
	if (rc != 0) {
		kfree(buf);
		return rc;
	}

	io_parms.netfid = netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = CIFS_MF_SYMLINK_FILE_SIZE;

	rc = CIFSSMBWrite(xid, &io_parms, &bytes_written, buf, NULL, 0);
	CIFSSMBClose(xid, tcon, netfid);
	kfree(buf);
	if (rc != 0)
		return rc;

	if (bytes_written != CIFS_MF_SYMLINK_FILE_SIZE)
		return -EIO;

	return 0;
}