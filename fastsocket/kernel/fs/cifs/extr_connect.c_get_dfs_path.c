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
struct nls_table {int dummy; } ;
struct dfs_info3_param {int dummy; } ;
struct cifs_ses {char* serverName; int /*<<< orphan*/  ipc_tid; } ;

/* Variables and functions */
 int CIFSGetDFSRefer (int,struct cifs_ses*,char const*,struct dfs_info3_param**,unsigned int*,struct nls_table const*,int) ; 
 int CIFSTCon (int,struct cifs_ses*,char*,int /*<<< orphan*/ *,struct nls_table const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SERVER_NAME_LEN_WITH_NULL ; 
 int /*<<< orphan*/  cFYI (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strnlen (char*,int) ; 

int
get_dfs_path(int xid, struct cifs_ses *pSesInfo, const char *old_path,
	     const struct nls_table *nls_codepage, unsigned int *pnum_referrals,
	     struct dfs_info3_param **preferrals, int remap)
{
	char *temp_unc;
	int rc = 0;

	*pnum_referrals = 0;
	*preferrals = NULL;

	if (pSesInfo->ipc_tid == 0) {
		temp_unc = kmalloc(2 /* for slashes */ +
			strnlen(pSesInfo->serverName,
				SERVER_NAME_LEN_WITH_NULL * 2)
				 + 1 + 4 /* slash IPC$ */  + 2,
				GFP_KERNEL);
		if (temp_unc == NULL)
			return -ENOMEM;
		temp_unc[0] = '\\';
		temp_unc[1] = '\\';
		strcpy(temp_unc + 2, pSesInfo->serverName);
		strcpy(temp_unc + 2 + strlen(pSesInfo->serverName), "\\IPC$");
		rc = CIFSTCon(xid, pSesInfo, temp_unc, NULL, nls_codepage);
		cFYI(1, "CIFS Tcon rc = %d ipc_tid = %d", rc, pSesInfo->ipc_tid);
		kfree(temp_unc);
	}
	if (rc == 0)
		rc = CIFSGetDFSRefer(xid, pSesInfo, old_path, preferrals,
				     pnum_referrals, nls_codepage, remap);
	/* BB map targetUNCs to dfs_info3 structures, here or
		in CIFSGetDFSRefer BB */

	return rc;
}