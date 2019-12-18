#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_6__ {int /*<<< orphan*/ * wdir; } ;
typedef  TYPE_1__ HB_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * _wopendir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_1__* opendir (char const*) ; 

HB_DIR* hb_opendir(const char *path)
{
#ifdef SYS_MINGW
    HB_DIR *dir;
    wchar_t path_utf16[MAX_PATH];

    if (!MultiByteToWideChar(CP_UTF8, 0, path, -1, path_utf16, MAX_PATH))
        return NULL;
    dir = malloc(sizeof(HB_DIR));
    if (dir == NULL)
        return NULL;
    dir->wdir = _wopendir(path_utf16);
    if (dir->wdir == NULL)
    {
        free(dir);
        return NULL;
    }
    return dir;
#else
    return opendir(path);
#endif
}