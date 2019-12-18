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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ time_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 unsigned int S_IFBLK ; 
 unsigned int S_IFCHR ; 
 int /*<<< orphan*/  ino ; 
 int /*<<< orphan*/  push_hdr (char*) ; 
 int /*<<< orphan*/  push_rest (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ,unsigned int,long,long,int,long,int /*<<< orphan*/ ,int,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpio_mknod(const char *name, unsigned int mode,
		       uid_t uid, gid_t gid, char dev_type,
		       unsigned int maj, unsigned int min)
{
	char s[256];
	time_t mtime = time(NULL);

	if (dev_type == 'b')
		mode |= S_IFBLK;
	else
		mode |= S_IFCHR;

	sprintf(s,"%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		ino++,			/* ino */
		mode,			/* mode */
		(long) uid,		/* uid */
		(long) gid,		/* gid */
		1,			/* nlink */
		(long) mtime,		/* mtime */
		0,			/* filesize */
		3,			/* major */
		1,			/* minor */
		maj,			/* rmajor */
		min,			/* rminor */
		(unsigned)strlen(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_rest(name);
	return 0;
}