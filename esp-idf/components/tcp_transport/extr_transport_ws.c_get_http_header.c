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
 char* strcasestr (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char*,char*) ; 
 char* trimwhitespace (char*) ; 

__attribute__((used)) static char *get_http_header(const char *buffer, const char *key)
{
    char *found = strcasestr(buffer, key);
    if (found) {
        found += strlen(key);
        char *found_end = strstr(found, "\r\n");
        if (found_end) {
            found_end[0] = 0;//terminal string

            return trimwhitespace(found);
        }
    }
    return NULL;
}