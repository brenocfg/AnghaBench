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
struct cifs_tcon {int /*<<< orphan*/  num_closes; int /*<<< orphan*/  ses; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {int LastWriteTime; scalar_t__ ByteCount; scalar_t__ FileID; } ;
typedef  TYPE_1__ CLOSE_REQ ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  SMB_COM_CLOSE ; 
 int SendReceiveNoRsp (int const,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cERROR (int,char*,int) ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int small_smb_init (int /*<<< orphan*/ ,int,struct cifs_tcon*,void**) ; 

int
CIFSSMBClose(const int xid, struct cifs_tcon *tcon, int smb_file_id)
{
	int rc = 0;
	CLOSE_REQ *pSMB = NULL;
	cFYI(1, "In CIFSSMBClose");

/* do not retry on dead session on close */
	rc = small_smb_init(SMB_COM_CLOSE, 3, tcon, (void **) &pSMB);
	if (rc == -EAGAIN)
		return 0;
	if (rc)
		return rc;

	pSMB->FileID = (__u16) smb_file_id;
	pSMB->LastWriteTime = 0xFFFFFFFF;
	pSMB->ByteCount = 0;
	rc = SendReceiveNoRsp(xid, tcon->ses, (char *) pSMB, 0);
	cifs_stats_inc(&tcon->num_closes);
	if (rc) {
		if (rc != -EINTR) {
			/* EINTR is expected when user ctl-c to kill app */
			cERROR(1, "Send error in Close = %d", rc);
		}
	}

	/* Since session is dead, file will be closed on server already */
	if (rc == -EAGAIN)
		rc = 0;

	return rc;
}