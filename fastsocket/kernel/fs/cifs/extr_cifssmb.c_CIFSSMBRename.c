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
struct cifs_tcon {int /*<<< orphan*/  num_renames; int /*<<< orphan*/  ses; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int Flags2; } ;
struct TYPE_6__ {int BufferFormat; int* OldFileName; void* ByteCount; TYPE_1__ hdr; void* SearchAttributes; } ;
typedef  int /*<<< orphan*/  RENAME_RSP ;
typedef  TYPE_2__ RENAME_REQ ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int ATTR_HIDDEN ; 
 int ATTR_READONLY ; 
 int ATTR_SYSTEM ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_RENAME ; 
 int SendReceive (int const,int /*<<< orphan*/ ,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int cifsConvertToUCS (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct nls_table const*,int) ; 
 int /*<<< orphan*/  cifs_buf_release (TYPE_2__*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  inc_rfc1001_len (TYPE_2__*,int) ; 
 int smb_init (int /*<<< orphan*/ ,int,struct cifs_tcon*,void**,void**) ; 
 int /*<<< orphan*/  strncpy (int*,char const*,int) ; 
 int strnlen (char const*,int /*<<< orphan*/ ) ; 

int
CIFSSMBRename(const int xid, struct cifs_tcon *tcon,
	      const char *fromName, const char *toName,
	      const struct nls_table *nls_codepage, int remap)
{
	int rc = 0;
	RENAME_REQ *pSMB = NULL;
	RENAME_RSP *pSMBr = NULL;
	int bytes_returned;
	int name_len, name_len2;
	__u16 count;

	cFYI(1, "In CIFSSMBRename");
renameRetry:
	rc = smb_init(SMB_COM_RENAME, 1, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	pSMB->BufferFormat = 0x04;
	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM |
			ATTR_DIRECTORY);

	if (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) {
		name_len =
		    cifsConvertToUCS((__le16 *) pSMB->OldFileName, fromName,
				     PATH_MAX, nls_codepage, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
		pSMB->OldFileName[name_len] = 0x04;	/* pad */
	/* protocol requires ASCII signature byte on Unicode string */
		pSMB->OldFileName[name_len + 1] = 0x00;
		name_len2 =
		    cifsConvertToUCS((__le16 *)&pSMB->OldFileName[name_len + 2],
				     toName, PATH_MAX, nls_codepage, remap);
		name_len2 += 1 /* trailing null */  + 1 /* Signature word */ ;
		name_len2 *= 2;	/* convert to bytes */
	} else {	/* BB improve the check for buffer overruns BB */
		name_len = strnlen(fromName, PATH_MAX);
		name_len++;	/* trailing null */
		strncpy(pSMB->OldFileName, fromName, name_len);
		name_len2 = strnlen(toName, PATH_MAX);
		name_len2++;	/* trailing null */
		pSMB->OldFileName[name_len] = 0x04;  /* 2nd buffer format */
		strncpy(&pSMB->OldFileName[name_len + 1], toName, name_len2);
		name_len2++;	/* trailing null */
		name_len2++;	/* signature byte */
	}

	count = 1 /* 1st signature byte */  + name_len + name_len2;
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	cifs_stats_inc(&tcon->num_renames);
	if (rc)
		cFYI(1, "Send error in rename = %d", rc);

	cifs_buf_release(pSMB);

	if (rc == -EAGAIN)
		goto renameRetry;

	return rc;
}