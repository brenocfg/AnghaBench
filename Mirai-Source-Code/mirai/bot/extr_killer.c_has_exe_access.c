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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  TABLE_KILLER_EXE ; 
 int /*<<< orphan*/  TABLE_KILLER_PROC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  getpid () ; 
 char* killer_realpath ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  table_lock_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_retrieve_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_unlock_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  util_itoa (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  util_strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  util_zero (char*,int) ; 

__attribute__((used)) static BOOL has_exe_access(void)
{
    char path[PATH_MAX], *ptr_path = path, tmp[16];
    int fd, k_rp_len;

    table_unlock_val(TABLE_KILLER_PROC);
    table_unlock_val(TABLE_KILLER_EXE);

    // Copy /proc/$pid/exe into path
    ptr_path += util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
    ptr_path += util_strcpy(ptr_path, util_itoa(getpid(), 10, tmp));
    ptr_path += util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_EXE, NULL));

    // Try to open file
    if ((fd = open(path, O_RDONLY)) == -1)
    {
#ifdef DEBUG
        printf("[killer] Failed to open()\n");
#endif
        return FALSE;
    }
    close(fd);

    table_lock_val(TABLE_KILLER_PROC);
    table_lock_val(TABLE_KILLER_EXE);

    if ((k_rp_len = readlink(path, killer_realpath, PATH_MAX - 1)) != -1)
    {
        killer_realpath[k_rp_len] = 0;
#ifdef DEBUG
        printf("[killer] Detected we are running out of `%s`\n", killer_realpath);
#endif
    }

    util_zero(path, ptr_path - path);

    return TRUE;
}