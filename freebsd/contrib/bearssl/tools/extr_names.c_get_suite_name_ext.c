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
 char* get_suite_name (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int strlen (char const*) ; 

int
get_suite_name_ext(unsigned suite, char *dst, size_t len)
{
	const char *name;
	char tmp[30];
	size_t n;

	name = get_suite_name(suite);
	if (name == NULL) {
		sprintf(tmp, "unknown (0x%04X)", suite);
		name = tmp;
	}
	n = 1 + strlen(name);
	if (n > len) {
		if (len > 0) {
			dst[0] = 0;
		}
		return -1;
	}
	memcpy(dst, name, n);
	return 0;
}