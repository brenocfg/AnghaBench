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
 char* get_curve_name (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char const*) ; 

int
get_curve_name_ext(int id, char *dst, size_t len)
{
	const char *name;
	char tmp[30];
	size_t n;

	name = get_curve_name(id);
	if (name == NULL) {
		sprintf(tmp, "unknown (%d)", id);
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