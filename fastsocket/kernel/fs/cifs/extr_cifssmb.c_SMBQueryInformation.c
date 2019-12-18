#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_sec; scalar_t__ tv_nsec; } ;
struct smb_hdr {int dummy; } ;
struct nls_table {int dummy; } ;
struct cifs_tcon {int /*<<< orphan*/  ses; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_12__ {int /*<<< orphan*/  Attributes; void* AllocationSize; void* EndOfFile; scalar_t__ LastAccessTime; void* ChangeTime; void* LastWriteTime; } ;
struct TYPE_9__ {int Flags2; } ;
struct TYPE_11__ {int BufferFormat; int /*<<< orphan*/  ByteCount; scalar_t__ FileName; TYPE_1__ hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  size; int /*<<< orphan*/  last_write_time; } ;
typedef  TYPE_2__ QUERY_INFORMATION_RSP ;
typedef  TYPE_3__ QUERY_INFORMATION_REQ ;
typedef  TYPE_4__ FILE_ALL_INFO ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_QUERY_INFORMATION ; 
 int SendReceive (int const,int /*<<< orphan*/ ,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int cifsConvertToUCS (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,struct nls_table const*,int) ; 
 int /*<<< orphan*/  cifs_UnixTimeToNT (struct timespec) ; 
 int /*<<< orphan*/  cifs_buf_release (TYPE_3__*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_rfc1001_len (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int smb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_tcon*,void**,void**) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,unsigned char const*,int) ; 
 int strnlen (unsigned char const*,int /*<<< orphan*/ ) ; 

int SMBQueryInformation(const int xid, struct cifs_tcon *tcon,
			const unsigned char *searchName,
			FILE_ALL_INFO *pFinfo,
			const struct nls_table *nls_codepage, int remap)
{
	QUERY_INFORMATION_REQ *pSMB;
	QUERY_INFORMATION_RSP *pSMBr;
	int rc = 0;
	int bytes_returned;
	int name_len;

	cFYI(1, "In SMBQPath path %s", searchName);
QInfRetry:
	rc = smb_init(SMB_COM_QUERY_INFORMATION, 0, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	if (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) {
		name_len =
			cifsConvertToUCS((__le16 *) pSMB->FileName, searchName,
					PATH_MAX, nls_codepage, remap);
		name_len++;     /* trailing null */
		name_len *= 2;
	} else {
		name_len = strnlen(searchName, PATH_MAX);
		name_len++;     /* trailing null */
		strncpy(pSMB->FileName, searchName, name_len);
	}
	pSMB->BufferFormat = 0x04;
	name_len++; /* account for buffer type byte */
	inc_rfc1001_len(pSMB, (__u16)name_len);
	pSMB->ByteCount = cpu_to_le16(name_len);

	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	if (rc) {
		cFYI(1, "Send error in QueryInfo = %d", rc);
	} else if (pFinfo) {
		struct timespec ts;
		__u32 time = le32_to_cpu(pSMBr->last_write_time);

		/* decode response */
		/* BB FIXME - add time zone adjustment BB */
		memset(pFinfo, 0, sizeof(FILE_ALL_INFO));
		ts.tv_nsec = 0;
		ts.tv_sec = time;
		/* decode time fields */
		pFinfo->ChangeTime = cpu_to_le64(cifs_UnixTimeToNT(ts));
		pFinfo->LastWriteTime = pFinfo->ChangeTime;
		pFinfo->LastAccessTime = 0;
		pFinfo->AllocationSize =
			cpu_to_le64(le32_to_cpu(pSMBr->size));
		pFinfo->EndOfFile = pFinfo->AllocationSize;
		pFinfo->Attributes =
			cpu_to_le32(le16_to_cpu(pSMBr->attr));
	} else
		rc = -EIO; /* bad buffer passed in */

	cifs_buf_release(pSMB);

	if (rc == -EAGAIN)
		goto QInfRetry;

	return rc;
}