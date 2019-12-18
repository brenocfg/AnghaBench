#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cifs_ses {int capabilities; TYPE_1__* server; } ;
typedef  int __u32 ;
struct TYPE_7__ {int /*<<< orphan*/  Flags2; } ;
struct TYPE_8__ {int AndXCommand; TYPE_2__ hdr; int /*<<< orphan*/  VcNumber; void* MaxMpxCount; void* MaxBufferSize; } ;
struct TYPE_9__ {TYPE_3__ req; } ;
struct TYPE_6__ {int sec_mode; int /*<<< orphan*/  maxReq; } ;
typedef  TYPE_4__ SESSION_SETUP_ANDX ;

/* Variables and functions */
 int CAP_DFS ; 
 int CAP_LARGE_FILES ; 
 int CAP_LARGE_READ_X ; 
 int CAP_LARGE_WRITE_X ; 
 int CAP_LEVEL_II_OPLOCKS ; 
 int CAP_NT_SMBS ; 
 int CAP_STATUS32 ; 
 int CAP_UNICODE ; 
 int CAP_UNIX ; 
 scalar_t__ CIFSMaxBufSize ; 
 scalar_t__ MAX_CIFS_HDR_SIZE ; 
 int SECMODE_SIGN_ENABLED ; 
 int SECMODE_SIGN_REQUIRED ; 
 int /*<<< orphan*/  SMBFLG2_DFS ; 
 int /*<<< orphan*/  SMBFLG2_ERR_STATUS ; 
 int /*<<< orphan*/  SMBFLG2_SECURITY_SIGNATURE ; 
 int /*<<< orphan*/  SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_next_vcnum (struct cifs_ses*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static __u32 cifs_ssetup_hdr(struct cifs_ses *ses, SESSION_SETUP_ANDX *pSMB)
{
	__u32 capabilities = 0;

	/* init fields common to all four types of SessSetup */
	/* Note that offsets for first seven fields in req struct are same  */
	/*	in CIFS Specs so does not matter which of 3 forms of struct */
	/*	that we use in next few lines                               */
	/* Note that header is initialized to zero in header_assemble */
	pSMB->req.AndXCommand = 0xFF;
	pSMB->req.MaxBufferSize = cpu_to_le16(min_t(u32,
					CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4,
					USHRT_MAX));
	pSMB->req.MaxMpxCount = cpu_to_le16(ses->server->maxReq);
	pSMB->req.VcNumber = get_next_vcnum(ses);

	/* Now no need to set SMBFLG_CASELESS or obsolete CANONICAL PATH */

	/* BB verify whether signing required on neg or just on auth frame
	   (and NTLM case) */

	capabilities = CAP_LARGE_FILES | CAP_NT_SMBS | CAP_LEVEL_II_OPLOCKS |
			CAP_LARGE_WRITE_X | CAP_LARGE_READ_X;

	if (ses->server->sec_mode &
	    (SECMODE_SIGN_REQUIRED | SECMODE_SIGN_ENABLED))
		pSMB->req.hdr.Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	if (ses->capabilities & CAP_UNICODE) {
		pSMB->req.hdr.Flags2 |= SMBFLG2_UNICODE;
		capabilities |= CAP_UNICODE;
	}
	if (ses->capabilities & CAP_STATUS32) {
		pSMB->req.hdr.Flags2 |= SMBFLG2_ERR_STATUS;
		capabilities |= CAP_STATUS32;
	}
	if (ses->capabilities & CAP_DFS) {
		pSMB->req.hdr.Flags2 |= SMBFLG2_DFS;
		capabilities |= CAP_DFS;
	}
	if (ses->capabilities & CAP_UNIX)
		capabilities |= CAP_UNIX;

	return capabilities;
}