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
 char* strrchr (char const*,char) ; 

char * hb_strr_dir_sep(const char *path)
{
#ifdef SYS_MINGW
    char *sep = strrchr(path, '/');
    if (sep == NULL)
        sep = strrchr(path, '\\');
    return sep;
#else
    return strrchr(path, '/');
#endif
}