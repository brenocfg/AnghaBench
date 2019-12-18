#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smb_vol {scalar_t__ seal; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; scalar_t__ nodfs; int /*<<< orphan*/  local_nls; int /*<<< orphan*/  UNC; scalar_t__ password; } ;
struct cifs_tcon {scalar_t__ seal; int Flags; int /*<<< orphan*/  tcon_list; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  password; struct cifs_ses* ses; } ;
struct cifs_ses {int /*<<< orphan*/  tcon_list; } ;

/* Variables and functions */
 int CIFSTCon (int,struct cifs_ses*,int /*<<< orphan*/ ,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct cifs_tcon* ERR_PTR (int) ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GetXid () ; 
 int SMB_SHARE_IS_IN_DFS ; 
 int /*<<< orphan*/  cERROR (int,char*) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 struct cifs_tcon* cifs_find_tcon (struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_fscache_get_super_cookie (struct cifs_tcon*) ; 
 int /*<<< orphan*/  cifs_put_smb_ses (struct cifs_ses*) ; 
 int /*<<< orphan*/  cifs_tcp_ses_lock ; 
 int /*<<< orphan*/  kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 struct cifs_tcon* tconInfoAlloc () ; 
 int /*<<< orphan*/  tconInfoFree (struct cifs_tcon*) ; 

__attribute__((used)) static struct cifs_tcon *
cifs_get_tcon(struct cifs_ses *ses, struct smb_vol *volume_info)
{
	int rc, xid;
	struct cifs_tcon *tcon;

	tcon = cifs_find_tcon(ses, volume_info->UNC);
	if (tcon) {
		cFYI(1, "Found match on UNC path");
		/* existing tcon already has a reference */
		cifs_put_smb_ses(ses);
		if (tcon->seal != volume_info->seal)
			cERROR(1, "transport encryption setting "
				   "conflicts with existing tid");
		return tcon;
	}

	tcon = tconInfoAlloc();
	if (tcon == NULL) {
		rc = -ENOMEM;
		goto out_fail;
	}

	tcon->ses = ses;
	if (volume_info->password) {
		tcon->password = kstrdup(volume_info->password, GFP_KERNEL);
		if (!tcon->password) {
			rc = -ENOMEM;
			goto out_fail;
		}
	}

	if (strchr(volume_info->UNC + 3, '\\') == NULL
	    && strchr(volume_info->UNC + 3, '/') == NULL) {
		cERROR(1, "Missing share name");
		rc = -ENODEV;
		goto out_fail;
	}

	/* BB Do we need to wrap session_mutex around
	 * this TCon call and Unix SetFS as
	 * we do on SessSetup and reconnect? */
	xid = GetXid();
	rc = CIFSTCon(xid, ses, volume_info->UNC, tcon, volume_info->local_nls);
	FreeXid(xid);
	cFYI(1, "CIFS Tcon rc = %d", rc);
	if (rc)
		goto out_fail;

	if (volume_info->nodfs) {
		tcon->Flags &= ~SMB_SHARE_IS_IN_DFS;
		cFYI(1, "DFS disabled (%d)", tcon->Flags);
	}
	tcon->seal = volume_info->seal;
	/* we can have only one retry value for a connection
	   to a share so for resources mounted more than once
	   to the same server share the last value passed in
	   for the retry flag is used */
	tcon->retry = volume_info->retry;
	tcon->nocase = volume_info->nocase;
	tcon->local_lease = volume_info->local_lease;

	spin_lock(&cifs_tcp_ses_lock);
	list_add(&tcon->tcon_list, &ses->tcon_list);
	spin_unlock(&cifs_tcp_ses_lock);

	cifs_fscache_get_super_cookie(tcon);

	return tcon;

out_fail:
	tconInfoFree(tcon);
	return ERR_PTR(rc);
}