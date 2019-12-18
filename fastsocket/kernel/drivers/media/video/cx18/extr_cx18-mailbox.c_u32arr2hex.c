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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *u32arr2hex(u32 data[], int n, char *buf)
{
	char *p;
	int i;

	for (i = 0, p = buf; i < n; i++, p += 11) {
		/* kernel snprintf() appends '\0' always */
		snprintf(p, 12, " %#010x", data[i]);
	}
	*p = '\0';
	return buf;
}