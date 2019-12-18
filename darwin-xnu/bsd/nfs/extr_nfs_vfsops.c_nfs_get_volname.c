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
struct TYPE_2__ {char* f_mntfromname; } ;
struct mount {TYPE_1__ mnt_vfsstat; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strnlen (char const*,int) ; 

__attribute__((used)) static void
nfs_get_volname(struct mount *mp, char *volname, size_t len)
{
	const char *ptr, *cptr;
	const char *mntfrom = mp->mnt_vfsstat.f_mntfromname;
	size_t mflen = strnlen(mntfrom, MAXPATHLEN+1);

	if (mflen > MAXPATHLEN || mflen == 0) {
		strlcpy(volname, "Bad volname", len);
		return;
	}

	/* Move back over trailing slashes */
	for (ptr = &mntfrom[mflen-1]; ptr != mntfrom && *ptr == '/'; ptr--) {
		mflen--;
	}

	/* Find first character after the last slash */
	cptr = ptr = NULL;
	for(size_t i = 0; i < mflen; i++) {
		if (mntfrom[i] == '/')
			ptr = &mntfrom[i+1];
		/* And the first character after the first colon */
		else if (cptr == NULL && mntfrom[i] == ':')
			cptr = &mntfrom[i+1];
	}

	/*
	 * No slash or nothing after the last slash
	 * use everything past the first colon
	 */
	if (ptr == NULL || *ptr == '\0')
		ptr = cptr;
	/* Otherwise use the mntfrom name */
	if (ptr == NULL)
		ptr = mntfrom;

	mflen = &mntfrom[mflen] - ptr;
	len = mflen+1 < len ? mflen+1 : len;

	strlcpy(volname, ptr, len);
}