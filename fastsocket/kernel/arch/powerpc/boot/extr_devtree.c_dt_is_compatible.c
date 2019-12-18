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
 int /*<<< orphan*/  MAX_PROP_LEN ; 
 int getprop (void*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ prop_buf ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 scalar_t__ strnlen (char*,int) ; 

int dt_is_compatible(void *node, const char *compat)
{
	char *buf = (char *)prop_buf;
	int len, pos;

	len = getprop(node, "compatible", buf, MAX_PROP_LEN);
	if (len < 0)
		return 0;

	for (pos = 0; pos < len; pos++) {
		if (!strcmp(buf + pos, compat))
			return 1;

		pos += strnlen(&buf[pos], len - pos);
	}

	return 0;
}