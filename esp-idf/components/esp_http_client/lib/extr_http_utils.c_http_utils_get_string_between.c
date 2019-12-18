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
 char* calloc (int,int) ; 
 int /*<<< orphan*/  mem_check (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

char *http_utils_get_string_between(const char *str, const char *begin, const char *end)
{
    char *found = strstr(str, begin);
    char *ret = NULL;
    if (found) {
        found += strlen(begin);
        char *found_end = strstr(found, end);
        if (found_end) {
            ret = calloc(1, found_end - found + 1);
            mem_check(ret);
            memcpy(ret, found, found_end - found);
            return ret;
        }
    }
    return NULL;
}