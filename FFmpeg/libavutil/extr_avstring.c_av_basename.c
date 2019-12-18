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
 char* FFMAX3 (char*,char*,char*) ; 
 char* strchr (char const*,char) ; 
 char* strrchr (char const*,char) ; 

const char *av_basename(const char *path)
{
    char *p;

    if (!path || *path == '\0')
        return ".";

    p = strrchr(path, '/');
#if HAVE_DOS_PATHS
    char *q = strrchr(path, '\\');
    char *d = strchr(path, ':');

    p = FFMAX3(p, q, d);
#endif

    if (!p)
        return path;

    return p + 1;
}