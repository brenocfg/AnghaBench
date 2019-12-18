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
 int /*<<< orphan*/  rulename ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static const char *
fmtname(const char *n) {
	size_t l = strlen(rulename);
	if (l == 0)
		return "*";
	if (strncmp(n, rulename, l) == 0) {
		if (n[l] != '\0')
			return n + l;
		else
			return "*";
	} else if (!*n)
		return "=";
	else
		return n;
}