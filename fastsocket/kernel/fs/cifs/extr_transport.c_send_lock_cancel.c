#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smb_hdr {int dummy; } ;
struct cifs_tcon {struct cifs_ses* ses; } ;
struct cifs_ses {int /*<<< orphan*/  server; } ;
struct TYPE_3__ {int /*<<< orphan*/  Mid; } ;
struct TYPE_4__ {int LockType; TYPE_1__ hdr; scalar_t__ Timeout; } ;
typedef  TYPE_2__ LOCK_REQ ;

/* Variables and functions */
 int /*<<< orphan*/  GetNextMid (int /*<<< orphan*/ ) ; 
 int LOCKING_ANDX_CANCEL_LOCK ; 
 int LOCKING_ANDX_LARGE_FILES ; 
 int SendReceive (unsigned int const,struct cifs_ses*,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_lock_cancel(const unsigned int xid, struct cifs_tcon *tcon,
			struct smb_hdr *in_buf,
			struct smb_hdr *out_buf)
{
	int bytes_returned;
	struct cifs_ses *ses = tcon->ses;
	LOCK_REQ *pSMB = (LOCK_REQ *)in_buf;

	/* We just modify the current in_buf to change
	   the type of lock from LOCKING_ANDX_SHARED_LOCK
	   or LOCKING_ANDX_EXCLUSIVE_LOCK to
	   LOCKING_ANDX_CANCEL_LOCK. */

	pSMB->LockType = LOCKING_ANDX_CANCEL_LOCK|LOCKING_ANDX_LARGE_FILES;
	pSMB->Timeout = 0;
	pSMB->hdr.Mid = GetNextMid(ses->server);

	return SendReceive(xid, ses, in_buf, out_buf,
			&bytes_returned, 0);
}