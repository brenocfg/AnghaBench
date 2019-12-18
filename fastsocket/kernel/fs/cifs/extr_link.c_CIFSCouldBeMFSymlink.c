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
struct cifs_fattr {int cf_mode; scalar_t__ cf_eof; } ;

/* Variables and functions */
 scalar_t__ CIFS_MF_SYMLINK_FILE_SIZE ; 
 int S_IFREG ; 

bool
CIFSCouldBeMFSymlink(const struct cifs_fattr *fattr)
{
	if (!(fattr->cf_mode & S_IFREG))
		/* it's not a symlink */
		return false;

	if (fattr->cf_eof != CIFS_MF_SYMLINK_FILE_SIZE)
		/* it's not a symlink */
		return false;

	return true;
}