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
typedef  char wchar_t ;

/* Variables and functions */

__attribute__((used)) static int in_set(const wchar_t *set, int c)
{
	int j;
	const wchar_t *p = set;
	if (*p == '-') {
		if (c=='-') return 1;
		p++;
	} else if (*p == ']') {
		if (c==']') return 1;
		p++;
	}
	for (; *p && *p != ']'; p++) {
		if (*p=='-' && p[1] && p[1] != ']')
			for (j=p++[-1]; j<*p; j++)
				if (c==j) return 1;
		if (c==*p) return 1;
	}
	return 0;
}