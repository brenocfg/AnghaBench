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
 int /*<<< orphan*/  lprintf (char*,char*) ; 
 int plat_get_root_dir (char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void emu_make_path(char *buff, const char *end, int size)
{
	int pos, end_len;

	end_len = strlen(end);
	pos = plat_get_root_dir(buff, size);
	strncpy(buff + pos, end, size - pos);
	buff[size - 1] = 0;
	if (pos + end_len > size - 1)
		lprintf("Warning: path truncated: %s\n", buff);
}