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
 int offset ; 
 int /*<<< orphan*/  push_hdr (char*) ; 
 int /*<<< orphan*/  push_rest (char const*) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void cpio_trailer(void)
{
	char s[256];
	const char name[] = "TRAILER!!!";

	sprintf(s, "%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",		/* magic */
		0,			/* ino */
		0,			/* mode */
		(long) 0,		/* uid */
		(long) 0,		/* gid */
		1,			/* nlink */
		(long) 0,		/* mtime */
		0,			/* filesize */
		0,			/* major */
		0,			/* minor */
		0,			/* rmajor */
		0,			/* rminor */
		(unsigned)strlen(name)+1, /* namesize */
		0);			/* chksum */
	push_hdr(s);
	push_rest(name);

	while (offset % 512) {
		putchar(0);
		offset++;
	}
}