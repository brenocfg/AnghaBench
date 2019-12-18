#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dirent {int d_namlen; int /*<<< orphan*/  d_reclen; int /*<<< orphan*/  d_ino; int /*<<< orphan*/  d_name; } ;
struct _wdirent {int /*<<< orphan*/  d_reclen; int /*<<< orphan*/  d_ino; int /*<<< orphan*/  d_name; } ;
struct TYPE_4__ {struct dirent entry; int /*<<< orphan*/  wdir; } ;
typedef  TYPE_1__ HB_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct _wdirent* _wreaddir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (TYPE_1__*) ; 

struct dirent * hb_readdir(HB_DIR *dir)
{
#ifdef SYS_MINGW
    struct _wdirent *entry;
    entry = _wreaddir(dir->wdir);
    if (entry == NULL)
        return NULL;

    int len = WideCharToMultiByte(CP_UTF8, 0, entry->d_name, -1,
                                  dir->entry.d_name, sizeof(dir->entry.d_name),
                                  NULL, NULL );
    dir->entry.d_ino = entry->d_ino;
    dir->entry.d_reclen = entry->d_reclen;
    dir->entry.d_namlen = len - 1;
    return &dir->entry;
#else
    return readdir(dir);
#endif
}