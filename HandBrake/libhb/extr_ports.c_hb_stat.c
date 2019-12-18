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
typedef  int /*<<< orphan*/  hb_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int _wstat64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stat (char const*,int /*<<< orphan*/ *) ; 

int hb_stat(const char *path, hb_stat_t *sb)
{
#ifdef SYS_MINGW
    wchar_t path_utf16[MAX_PATH];
    if (!MultiByteToWideChar(CP_UTF8, 0, path, -1, path_utf16, MAX_PATH))
        return -1;
    return _wstat64( path_utf16, sb );
#else
    return stat(path, sb);
#endif
}