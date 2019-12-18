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
 int /*<<< orphan*/  IS_IDENTIFIER_CHAR (char const) ; 

__attribute__((used)) static int strmatch(const char *s, const char *prefix)
{
    int i;
    for (i=0; prefix[i]; i++) {
        if (prefix[i] != s[i]) return 0;
    }
    /* return 1 only if the s identifier is terminated */
    return !IS_IDENTIFIER_CHAR(s[i]);
}