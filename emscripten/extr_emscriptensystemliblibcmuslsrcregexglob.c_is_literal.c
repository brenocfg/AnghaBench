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

__attribute__((used)) static int is_literal(const char *p, int useesc)
{
	int bracket = 0;
	for (; *p; p++) {
		switch (*p) {
		case '\\':
			if (!useesc) break;
		case '?':
		case '*':
			return 0;
		case '[':
			bracket = 1;
			break;
		case ']':
			if (bracket) return 0;
			break;
		}
	}
	return 1;
}