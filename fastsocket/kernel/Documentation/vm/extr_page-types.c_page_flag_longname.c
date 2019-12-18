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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 char** page_flag_names ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static char *page_flag_longname(uint64_t flags)
{
	static char buf[1024];
	int i, n;

	for (i = 0, n = 0; i < ARRAY_SIZE(page_flag_names); i++) {
		if (!page_flag_names[i])
			continue;
		if ((flags >> i) & 1)
			n += snprintf(buf + n, sizeof(buf) - n, "%s,",
					page_flag_names[i] + 2);
	}
	if (n)
		n--;
	buf[n] = '\0';

	return buf;
}