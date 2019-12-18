#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct smb_hdr {int dummy; } ;
struct nls_table {int dummy; } ;
struct cifs_tcon {int /*<<< orphan*/  num_rmdirs; int /*<<< orphan*/  ses; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int Flags2; } ;
struct TYPE_6__ {int BufferFormat; int /*<<< orphan*/  ByteCount; scalar_t__ DirName; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  DELETE_DIRECTORY_RSP ;
typedef  TYPE_2__ DELETE_DIRECTORY_REQ ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_DELETE_DIRECTORY ; 
 int SendReceive (int const,int /*<<< orphan*/ ,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int cifsConvertToUCS (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct nls_table const*,int) ; 
 int /*<<< orphan*/  cifs_buf_release (TYPE_2__*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  inc_rfc1001_len (TYPE_2__*,int) ; 
 int smb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_tcon*,void**,void**) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,char const*,int) ; 
 int strnlen (char const*,int /*<<< orphan*/ ) ; 

int
CIFSSMBRmDir(const int xid, struct cifs_tcon *tcon, const char *dirName,
	     const struct nls_table *nls_codepage, int remap)
{
	DELETE_DIRECTORY_REQ *pSMB = NULL;
	DELETE_DIRECTORY_RSP *pSMBr = NULL;
	int rc = 0;
	int bytes_returned;
	int name_len;

	cFYI(1, "In CIFSSMBRmDir");
RmDirRetry:
	rc = smb_init(SMB_COM_DELETE_DIRECTORY, 0, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	if (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) {
		name_len = cifsConvertToUCS((__le16 *) pSMB->DirName, dirName,
					 PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	} else {		/* BB improve check for buffer overruns BB */
		name_len = strnlen(dirName, PATH_MAX);
		name_len++;	/* trailing null */
		strncpy(pSMB->DirName, dirName, name_len);
	}

	pSMB->BufferFormat = 0x04;
	inc_rfc1001_len(pSMB, name_len + 1);
	pSMB->ByteCount = cpu_to_le16(name_len + 1);
	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	cifs_stats_inc(&tcon->num_rmdirs);
	if (rc)
		cFYI(1, "Error in RMDir = %d", rc);

	cifs_buf_release(pSMB);
	if (rc == -EAGAIN)
		goto RmDirRetry;
	return rc;
}