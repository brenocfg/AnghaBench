#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pathwfs ;
struct TYPE_5__ {scalar_t__ (* overwrite_cb ) (void*,int /*<<< orphan*/ ,TYPE_2__*,char*) ;TYPE_2__* file_info; int /*<<< orphan*/  zip_handle; int /*<<< orphan*/  overwrite_userdata; int /*<<< orphan*/  entry_userdata; int /*<<< orphan*/  (* entry_cb ) (void*,int /*<<< orphan*/ ,TYPE_2__*,char*) ;} ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  directory ;
struct TYPE_6__ {int /*<<< orphan*/  external_fa; int /*<<< orphan*/  version_madeby; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  accessed_date; int /*<<< orphan*/  modified_date; int /*<<< orphan*/  linkname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_HOST_SYSTEM (int /*<<< orphan*/ ) ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_CREATE ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_PATH_SLASH_UNIX ; 
 int /*<<< orphan*/  MZ_VERSION_MADEBY_HOST_SYSTEM ; 
 scalar_t__ mz_dir_make (char*) ; 
 scalar_t__ mz_os_file_exists (char*) ; 
 scalar_t__ mz_os_is_dir (char*) ; 
 int /*<<< orphan*/  mz_os_make_symlink (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_os_set_file_attribs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_os_set_file_date (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_os_unlink (char*) ; 
 int /*<<< orphan*/  mz_path_convert_slashes (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_path_remove_filename (char*) ; 
 int /*<<< orphan*/  mz_path_remove_slash (char*) ; 
 int /*<<< orphan*/  mz_stream_close (void*) ; 
 int /*<<< orphan*/  mz_stream_delete (void**) ; 
 int /*<<< orphan*/  mz_stream_os_create (void**) ; 
 scalar_t__ mz_stream_os_open (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_write ; 
 scalar_t__ mz_zip_attrib_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_entry_is_dir (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_entry_is_symlink (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_reader_entry_save (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_reader_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 scalar_t__ stub2 (void*,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

int32_t mz_zip_reader_entry_save_file(void *handle, const char *path)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    void *stream = NULL;
    uint32_t target_attrib = 0;
    int32_t err_attrib = 0;
    int32_t err = MZ_OK;
    int32_t err_cb = MZ_OK;
    char pathwfs[512];
    char directory[512];

    if (mz_zip_reader_is_open(reader) != MZ_OK)
        return MZ_PARAM_ERROR;
    if (reader->file_info == NULL || path == NULL)
        return MZ_PARAM_ERROR;

    /* Convert to forward slashes for unix which doesn't like backslashes */
    strncpy(pathwfs, path, sizeof(pathwfs) - 1);
    pathwfs[sizeof(pathwfs) - 1] = 0;
    mz_path_convert_slashes(pathwfs, MZ_PATH_SLASH_UNIX);

    if (reader->entry_cb != NULL)
        reader->entry_cb(handle, reader->entry_userdata, reader->file_info, pathwfs);

    strncpy(directory, pathwfs, sizeof(directory) - 1);
    directory[sizeof(directory) - 1] = 0;
    mz_path_remove_filename(directory);

    /* If it is a directory entry then create a directory instead of writing file */
    if ((mz_zip_entry_is_dir(reader->zip_handle) == MZ_OK) &&
        (mz_zip_entry_is_symlink(reader->zip_handle) != MZ_OK))
    {
        err = mz_dir_make(directory);
        return err;
    }

    /* Check if file exists and ask if we want to overwrite */
    if ((mz_os_file_exists(pathwfs) == MZ_OK) && (reader->overwrite_cb != NULL))
    {
        err_cb = reader->overwrite_cb(handle, reader->overwrite_userdata, reader->file_info, pathwfs);
        if (err_cb != MZ_OK)
            return err;
        /* We want to overwrite the file so we delete the existing one */
        mz_os_unlink(pathwfs);
    }

    /* If symbolic link then properly construct destination path and link path */
    if (mz_zip_entry_is_symlink(reader->zip_handle) == MZ_OK)
    {
        mz_path_remove_slash(pathwfs);
        mz_path_remove_filename(directory);
    }

    /* Create the output directory if it doesn't already exist */
    if (mz_os_is_dir(directory) != MZ_OK)
    {
        err = mz_dir_make(directory);
        if (err != MZ_OK)
            return err;
    }

    /* If it is a symbolic link then create symbolic link instead of writing file */
    if (mz_zip_entry_is_symlink(reader->zip_handle) == MZ_OK)
    {
        mz_os_make_symlink(pathwfs, reader->file_info->linkname);
        /* Don't check return value because we aren't validating symbolic link target */
        return err;
    }

    /* Create the file on disk so we can save to it */
    mz_stream_os_create(&stream);
    err = mz_stream_os_open(stream, pathwfs, MZ_OPEN_MODE_CREATE);

    if (err == MZ_OK)
        err = mz_zip_reader_entry_save(handle, stream, mz_stream_write);

    mz_stream_close(stream);
    mz_stream_delete(&stream);

    if (err == MZ_OK)
    {
        /* Set the time of the file that has been created */
        mz_os_set_file_date(pathwfs, reader->file_info->modified_date,
            reader->file_info->accessed_date, reader->file_info->creation_date);
    }

    if (err == MZ_OK)
    {
        /* Set file attributes for the correct system */
        err_attrib = mz_zip_attrib_convert(MZ_HOST_SYSTEM(reader->file_info->version_madeby),
            reader->file_info->external_fa, MZ_VERSION_MADEBY_HOST_SYSTEM, &target_attrib);

        if (err_attrib == MZ_OK)
            mz_os_set_file_attribs(pathwfs, target_attrib);
    }

    return err;
}