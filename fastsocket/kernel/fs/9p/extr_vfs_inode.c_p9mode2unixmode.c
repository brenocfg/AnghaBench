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
struct v9fs_session_info {scalar_t__ nodev; } ;

/* Variables and functions */
 int P9_DMDEVICE ; 
 int P9_DMDIR ; 
 int P9_DMNAMEDPIPE ; 
 int P9_DMSETGID ; 
 int P9_DMSETUID ; 
 int P9_DMSETVTX ; 
 int P9_DMSOCKET ; 
 int P9_DMSYMLINK ; 
 int S_IFBLK ; 
 int S_IFDIR ; 
 int S_IFIFO ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 int S_IFSOCK ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 scalar_t__ v9fs_extended (struct v9fs_session_info*) ; 

__attribute__((used)) static int p9mode2unixmode(struct v9fs_session_info *v9ses, int mode)
{
	int res;

	res = mode & 0777;

	if ((mode & P9_DMDIR) == P9_DMDIR)
		res |= S_IFDIR;
	else if ((mode & P9_DMSYMLINK) && (v9fs_extended(v9ses)))
		res |= S_IFLNK;
	else if ((mode & P9_DMSOCKET) && (v9fs_extended(v9ses))
		 && (v9ses->nodev == 0))
		res |= S_IFSOCK;
	else if ((mode & P9_DMNAMEDPIPE) && (v9fs_extended(v9ses))
		 && (v9ses->nodev == 0))
		res |= S_IFIFO;
	else if ((mode & P9_DMDEVICE) && (v9fs_extended(v9ses))
		 && (v9ses->nodev == 0))
		res |= S_IFBLK;
	else
		res |= S_IFREG;

	if (v9fs_extended(v9ses)) {
		if ((mode & P9_DMSETUID) == P9_DMSETUID)
			res |= S_ISUID;

		if ((mode & P9_DMSETGID) == P9_DMSETGID)
			res |= S_ISGID;

		if ((mode & P9_DMSETVTX) == P9_DMSETVTX)
			res |= S_ISVTX;
	}

	return res;
}