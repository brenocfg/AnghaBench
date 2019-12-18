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
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int strlen (char*) ; 

void http_utils_trim_whitespace(char **str)
{
    char *end, *start;
    if (str == NULL) {
        return;
    }
    start = *str;
    if (start == NULL) {
        return;
    }
    // Trim leading space
    while (isspace((unsigned char)*start)) start ++;

    if (*start == 0) {  // All spaces?
        **str = 0;
        return;
    }

    // Trim trailing space
    end = (char *)(start + strlen(start) - 1);
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // Write new null terminator
    *(end + 1) = 0;
    memmove(*str, start, strlen(start) + 1);
}