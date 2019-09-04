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
 int /*<<< orphan*/  av_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int) ; 
 scalar_t__ av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char const*,char*) ; 

void ff_make_absolute_url(char *buf, int size, const char *base,
                          const char *rel)
{
    char *sep, *path_query;
    /* Absolute path, relative to the current server */
    if (base && strstr(base, "://") && rel[0] == '/') {
        if (base != buf)
            av_strlcpy(buf, base, size);
        sep = strstr(buf, "://");
        if (sep) {
            /* Take scheme from base url */
            if (rel[1] == '/') {
                sep[1] = '\0';
            } else {
                /* Take scheme and host from base url */
                sep += 3;
                sep = strchr(sep, '/');
                if (sep)
                    *sep = '\0';
            }
        }
        av_strlcat(buf, rel, size);
        return;
    }
    /* If rel actually is an absolute url, just copy it */
    if (!base || strstr(rel, "://") || rel[0] == '/') {
        av_strlcpy(buf, rel, size);
        return;
    }
    if (base != buf)
        av_strlcpy(buf, base, size);

    /* Strip off any query string from base */
    path_query = strchr(buf, '?');
    if (path_query)
        *path_query = '\0';

    /* Is relative path just a new query part? */
    if (rel[0] == '?') {
        av_strlcat(buf, rel, size);
        return;
    }

    /* Remove the file name from the base url */
    sep = strrchr(buf, '/');
    if (sep)
        sep[1] = '\0';
    else
        buf[0] = '\0';
    while (av_strstart(rel, "../", NULL) && sep) {
        /* Remove the path delimiter at the end */
        sep[0] = '\0';
        sep = strrchr(buf, '/');
        /* If the next directory name to pop off is "..", break here */
        if (!strcmp(sep ? &sep[1] : buf, "..")) {
            /* Readd the slash we just removed */
            av_strlcat(buf, "/", size);
            break;
        }
        /* Cut off the directory name */
        if (sep)
            sep[1] = '\0';
        else
            buf[0] = '\0';
        rel += 3;
    }
    av_strlcat(buf, rel, size);
}