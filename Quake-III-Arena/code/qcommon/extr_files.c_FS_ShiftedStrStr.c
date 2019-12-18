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
 int MAX_STRING_TOKENS ; 
 char* strstr (char const*,char*) ; 

char *FS_ShiftedStrStr(const char *string, const char *substring, int shift) {
	char buf[MAX_STRING_TOKENS];
	int i;

	for (i = 0; substring[i]; i++) {
		buf[i] = substring[i] + shift;
	}
	buf[i] = '\0';
	return strstr(string, buf);
}