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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ _wfopen_s (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 

FILE * hb_fopen(const char *path, const char *mode)
{
#ifdef SYS_MINGW
    FILE *f;
    wchar_t path_utf16[MAX_PATH];
    wchar_t mode_utf16[16];
    if (!MultiByteToWideChar(CP_UTF8, 0, path, -1, path_utf16, MAX_PATH))
        return NULL;
    if (!MultiByteToWideChar(CP_UTF8, 0, mode, -1, mode_utf16, 16))
        return NULL;
    errno_t ret = _wfopen_s(&f, path_utf16, mode_utf16);
    if (ret)
        return NULL;
    return f;
#else
    return fopen(path, mode);
#endif
}