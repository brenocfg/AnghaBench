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
 size_t SIZE_MAX ; 
 char* av_malloc (size_t) ; 
 char* av_strdup (char const*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char *av_append_path_component(const char *path, const char *component)
{
    size_t p_len, c_len;
    char *fullpath;

    if (!path)
        return av_strdup(component);
    if (!component)
        return av_strdup(path);

    p_len = strlen(path);
    c_len = strlen(component);
    if (p_len > SIZE_MAX - c_len || p_len + c_len > SIZE_MAX - 2)
        return NULL;
    fullpath = av_malloc(p_len + c_len + 2);
    if (fullpath) {
        if (p_len) {
            av_strlcpy(fullpath, path, p_len + 1);
            if (c_len) {
                if (fullpath[p_len - 1] != '/' && component[0] != '/')
                    fullpath[p_len++] = '/';
                else if (fullpath[p_len - 1] == '/' && component[0] == '/')
                    p_len--;
            }
        }
        av_strlcpy(&fullpath[p_len], component, c_len + 1);
        fullpath[p_len + c_len] = 0;
    }
    return fullpath;
}