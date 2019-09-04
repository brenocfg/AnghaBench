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

/* Variables and functions */
 int NFS_IDMAP_CTRL_FALLBACK_NO_COMMON_IDS ; 
 int nfs_idmap_ctrl ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 size_t strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *
nfs4_fallback_id(int numid, int isgrp, char *buf, size_t size)
{
	const char *idp = NULL;

	if (!(nfs_idmap_ctrl & NFS_IDMAP_CTRL_FALLBACK_NO_COMMON_IDS)) {
		/* map well known uid's to strings */
		if (numid == 0)
			idp = isgrp ? "wheel" : "root";
		else if (numid == -2)
			idp = "nobody";
	}
	if (!idp) {
		/* or just use a decimal number string. */
		snprintf(buf, size-1, "%d", numid);
		buf[size-1] = '\0';
	} else {
		size_t idplen = strlcpy(buf, idp, size);
		if (idplen >= size)
			return (NULL);
	}

	return (buf);
}