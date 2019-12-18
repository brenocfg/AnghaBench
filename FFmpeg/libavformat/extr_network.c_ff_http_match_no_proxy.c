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
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_strdup (char const*) ; 
 scalar_t__ match_host_pattern (char*,char const*) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 

int ff_http_match_no_proxy(const char *no_proxy, const char *hostname)
{
    char *buf, *start;
    int ret = 0;
    if (!no_proxy)
        return 0;
    if (!hostname)
        return 0;
    buf = av_strdup(no_proxy);
    if (!buf)
        return 0;
    start = buf;
    while (start) {
        char *sep, *next = NULL;
        start += strspn(start, " ,");
        sep = start + strcspn(start, " ,");
        if (*sep) {
            next = sep + 1;
            *sep = '\0';
        }
        if (match_host_pattern(start, hostname)) {
            ret = 1;
            break;
        }
        start = next;
    }
    av_free(buf);
    return ret;
}