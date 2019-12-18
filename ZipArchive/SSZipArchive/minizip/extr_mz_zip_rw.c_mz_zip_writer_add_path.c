#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  path_dir ;
struct TYPE_2__ {scalar_t__ store_links; int /*<<< orphan*/  follow_links; } ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  full_path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ MZ_EXIST_ERROR ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  mz_os_close_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ mz_os_is_dir (char const*) ; 
 scalar_t__ mz_os_is_symlink (char const*) ; 
 int /*<<< orphan*/ * mz_os_open_dir (char const*) ; 
 struct dirent* mz_os_read_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_path_combine (char*,char const*,int) ; 
 scalar_t__ mz_path_compare_wc (char const*,char*,int) ; 
 scalar_t__ mz_path_get_filename (char const*,char const**) ; 
 int /*<<< orphan*/  mz_path_remove_filename (char*) ; 
 scalar_t__ mz_zip_writer_add_file (void*,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/ * strrchr (char const*,char) ; 

int32_t mz_zip_writer_add_path(void *handle, const char *path, const char *root_path,
    uint8_t include_path, uint8_t recursive)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    int32_t err = MZ_OK;
    int16_t is_dir = 0;
    const char *filename = NULL;
    const char *filenameinzip = path;
    char *wildcard_ptr = NULL;
    char full_path[1024];
    char path_dir[1024];


    if (strrchr(path, '*') != NULL)
    {
        strncpy(path_dir, path, sizeof(path_dir) - 1);
        path_dir[sizeof(path_dir) - 1] = 0;
        mz_path_remove_filename(path_dir);
        wildcard_ptr = path_dir + strlen(path_dir) + 1;
        root_path = path = path_dir;
    }
    else
    {
        if (mz_os_is_dir(path) == MZ_OK)
            is_dir = 1;

        /* Construct the filename that our file will be stored in the zip as */
        if (root_path == NULL)
            root_path = path;

        /* Should the file be stored with any path info at all? */
        if (!include_path)
        {
            if (!is_dir && root_path == path)
            {
                if (mz_path_get_filename(filenameinzip, &filename) == MZ_OK)
                    filenameinzip = filename;
            }
            else
            {
                filenameinzip += strlen(root_path);
            }
        }

        if (!writer->store_links && !writer->follow_links)
        {
            if (mz_os_is_symlink(path) == MZ_OK)
                return err;
        }

        if (*filenameinzip != 0)
            err = mz_zip_writer_add_file(handle, path, filenameinzip);

        if (!is_dir)
            return err;

        if (writer->store_links)
        {
            if (mz_os_is_symlink(path) == MZ_OK)
                return err;
        }
    }

    dir = mz_os_open_dir(path);

    if (dir == NULL)
        return MZ_EXIST_ERROR;

    while ((entry = mz_os_read_dir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        full_path[0] = 0;
        mz_path_combine(full_path, path, sizeof(full_path));
        mz_path_combine(full_path, entry->d_name, sizeof(full_path));

        if (!recursive && mz_os_is_dir(full_path) == MZ_OK)
            continue;

        if ((wildcard_ptr != NULL) && (mz_path_compare_wc(entry->d_name, wildcard_ptr, 1) != MZ_OK))
            continue;

        err = mz_zip_writer_add_path(handle, full_path, root_path, include_path, recursive);
        if (err != MZ_OK)
            return err;
    }

    mz_os_close_dir(dir);
    return MZ_OK;
}