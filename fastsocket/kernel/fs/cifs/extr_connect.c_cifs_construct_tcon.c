#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct smb_vol {char* username; int linux_uid; int cred_uid; int no_linux_ext; int /*<<< orphan*/  secFlg; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  UNC; int /*<<< orphan*/  local_nls; } ;
struct cifs_tcon {int capabilities; TYPE_1__* ses; int /*<<< orphan*/  unix_ext; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  treeName; } ;
struct cifs_ses {int capabilities; TYPE_1__* ses; int /*<<< orphan*/  unix_ext; int /*<<< orphan*/  local_lease; int /*<<< orphan*/  nocase; int /*<<< orphan*/  retry; int /*<<< orphan*/  treeName; } ;
struct cifs_sb_info {int /*<<< orphan*/  local_nls; } ;
struct TYPE_5__ {int /*<<< orphan*/  srv_count; } ;
struct TYPE_4__ {TYPE_2__* server; } ;

/* Variables and functions */
 int CAP_UNIX ; 
 int /*<<< orphan*/  CIFSSEC_MUST_KRB5 ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cifs_tcon* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct cifs_tcon*) ; 
 int /*<<< orphan*/  MAX_USERNAME_SIZE ; 
 struct cifs_tcon* cifs_get_smb_ses (TYPE_2__*,struct smb_vol*) ; 
 struct cifs_tcon* cifs_get_tcon (struct cifs_tcon*,struct smb_vol*) ; 
 int /*<<< orphan*/  cifs_put_smb_ses (struct cifs_tcon*) ; 
 int /*<<< orphan*/  cifs_put_tcp_session (TYPE_2__*) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_tcp_ses_lock ; 
 int /*<<< orphan*/  kfree (struct smb_vol*) ; 
 struct smb_vol* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_cifs_unix_caps (int /*<<< orphan*/ ,struct cifs_tcon*,int /*<<< orphan*/ *,struct smb_vol*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cifs_tcon *
cifs_construct_tcon(struct cifs_sb_info *cifs_sb, uid_t fsuid)
{
	struct cifs_tcon *master_tcon = cifs_sb_master_tcon(cifs_sb);
	struct cifs_ses *ses;
	struct cifs_tcon *tcon = NULL;
	struct smb_vol *vol_info;
	char username[MAX_USERNAME_SIZE + 1];

	vol_info = kzalloc(sizeof(*vol_info), GFP_KERNEL);
	if (vol_info == NULL) {
		tcon = ERR_PTR(-ENOMEM);
		goto out;
	}

	snprintf(username, MAX_USERNAME_SIZE, "krb50x%x", fsuid);
	vol_info->username = username;
	vol_info->local_nls = cifs_sb->local_nls;
	vol_info->linux_uid = fsuid;
	vol_info->cred_uid = fsuid;
	vol_info->UNC = master_tcon->treeName;
	vol_info->retry = master_tcon->retry;
	vol_info->nocase = master_tcon->nocase;
	vol_info->local_lease = master_tcon->local_lease;
	vol_info->no_linux_ext = !master_tcon->unix_ext;

	/* FIXME: allow for other secFlg settings */
	vol_info->secFlg = CIFSSEC_MUST_KRB5;

	/* get a reference for the same TCP session */
	spin_lock(&cifs_tcp_ses_lock);
	++master_tcon->ses->server->srv_count;
	spin_unlock(&cifs_tcp_ses_lock);

	ses = cifs_get_smb_ses(master_tcon->ses->server, vol_info);
	if (IS_ERR(ses)) {
		tcon = (struct cifs_tcon *)ses;
		cifs_put_tcp_session(master_tcon->ses->server);
		goto out;
	}

	tcon = cifs_get_tcon(ses, vol_info);
	if (IS_ERR(tcon)) {
		cifs_put_smb_ses(ses);
		goto out;
	}

	if (ses->capabilities & CAP_UNIX)
		reset_cifs_unix_caps(0, tcon, NULL, vol_info);
out:
	kfree(vol_info);

	return tcon;
}