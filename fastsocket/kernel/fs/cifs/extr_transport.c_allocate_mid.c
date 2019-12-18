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
struct smb_hdr {scalar_t__ Command; } ;
struct mid_q_entry {int /*<<< orphan*/  qhead; } ;
struct cifs_ses {scalar_t__ status; TYPE_1__* server; } ;
struct TYPE_2__ {scalar_t__ tcpStatus; int /*<<< orphan*/  pending_mid_q; } ;

/* Variables and functions */
 struct mid_q_entry* AllocMidQEntry (struct smb_hdr*,TYPE_1__*) ; 
 scalar_t__ CifsExiting ; 
 scalar_t__ CifsGood ; 
 scalar_t__ CifsNeedReconnect ; 
 int EAGAIN ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 scalar_t__ SMB_COM_NEGOTIATE ; 
 scalar_t__ SMB_COM_SESSION_SETUP_ANDX ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allocate_mid(struct cifs_ses *ses, struct smb_hdr *in_buf,
			struct mid_q_entry **ppmidQ)
{
	if (ses->server->tcpStatus == CifsExiting) {
		return -ENOENT;
	}

	if (ses->server->tcpStatus == CifsNeedReconnect) {
		cFYI(1, "tcp session dead - return to caller to retry");
		return -EAGAIN;
	}

	if (ses->status != CifsGood) {
		/* check if SMB session is bad because we are setting it up */
		if ((in_buf->Command != SMB_COM_SESSION_SETUP_ANDX) &&
			(in_buf->Command != SMB_COM_NEGOTIATE))
			return -EAGAIN;
		/* else ok - we are setting up session */
	}
	*ppmidQ = AllocMidQEntry(in_buf, ses->server);
	if (*ppmidQ == NULL)
		return -ENOMEM;
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&(*ppmidQ)->qhead, &ses->server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);
	return 0;
}