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
 int /*<<< orphan*/  GFP_NOFS ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *setup_root_args(char *args)
{
	unsigned len = strlen(args) + 2 + 1;
	char *src, *dst, *buf;

	/*
	 * We need the same args as before, but with this substitution:
	 * s!subvol=[^,]+!subvolid=0!
	 *
	 * Since the replacement string is up to 2 bytes longer than the
	 * original, allocate strlen(args) + 2 + 1 bytes.
	 */

	src = strstr(args, "subvol=");
	/* This shouldn't happen, but just in case.. */
	if (!src)
		return NULL;

	buf = dst = kmalloc(len, GFP_NOFS);
	if (!buf)
		return NULL;

	/*
	 * If the subvol= arg is not at the start of the string,
	 * copy whatever precedes it into buf.
	 */
	if (src != args) {
		*src++ = '\0';
		strcpy(buf, args);
		dst += strlen(args);
	}

	strcpy(dst, "subvolid=0");
	dst += strlen("subvolid=0");

	/*
	 * If there is a "," after the original subvol=... string,
	 * copy that suffix into our buffer.  Otherwise, we're done.
	 */
	src = strchr(src, ',');
	if (src)
		strcpy(dst, src);

	return buf;
}